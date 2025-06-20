#include "ausgabetabelle.h"
#include "datenbank.h"
#include "fenster1.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <algorithm>

// Konstruktor der Ausgabetabelle
ausgabetabelle::ausgabetabelle(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Ausgabetabelle");

    // Hauptlayout erstellen
    auto *mainLayout = new QVBoxLayout(this);

    // Tabelle vorbereiten (3 Spalten: Checkbox, Name, Alter)
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "" << "Name" << "Alter");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // Nicht editierbar

    mainLayout->addWidget(tableWidget);

    // Buttons erstellen
    btnSpeichern = new QPushButton("Speichern", this);
    btnLoeschen = new QPushButton("Ausgewählte löschen", this);
    neuhinzufügen = new QPushButton("Neuhinzufügen", this);

    // Buttons zum Layout hinzufügen
    mainLayout->addWidget(btnSpeichern);
    mainLayout->addWidget(btnLoeschen);
    mainLayout->addWidget(neuhinzufügen);

    setLayout(mainLayout);
    setPersonen(Datenbank::lesePersonenAusDatei());

    // Speichern-Button: speichert Personen in Datei
    connect(btnSpeichern, &QPushButton::clicked, this, [this]() {
        if (Datenbank::schreibePersonenInDatei(personen)) {
            QMessageBox::information(this, "Erfolg", "Datei gespeichert.");
        } else {
            QMessageBox::warning(this, "Fehler", "Datei konnte nicht gespeichert werden.");
        }
    });

    // Löschen-Button: ausgewählte Zeilen entfernen
    connect(btnLoeschen, &QPushButton::clicked, this, [this]() {// geht über die checkboxen in der ersten Spalte und guckt, welche ausgewählt sind
        std::vector<int> zeilenZuLoeschen;
        for (int i = 0; i < tableWidget->rowCount(); ++i) {
            QWidget* widget = tableWidget->cellWidget(i, 0);
            if (widget) {
                QCheckBox* cb = widget->findChild<QCheckBox*>();
                if (cb && cb->isChecked())
                    zeilenZuLoeschen.push_back(i);
            }
        }

        // Indizes absteigend sortieren, damit beim Entfernen keine Verschiebung entsteht
        std::sort(zeilenZuLoeschen.rbegin(), zeilenZuLoeschen.rend());

        // Personen im Vektor entfernen
        Datenbank::loeschePersonen(personen, zeilenZuLoeschen);

        // Zeilen aus Tabelle entfernen
        for (int idx : zeilenZuLoeschen)
            tableWidget->removeRow(idx);

        // Neue Daten speichern
        Datenbank::schreibePersonenInDatei(personen);
    });

    // Neuhinzufügen-Button: öffnet Fenster1 zur Eingabe
    connect(neuhinzufügen, &QPushButton::clicked, this, [this]() {
        Fenster1 *neuesFenster = new Fenster1();
        // Verbindung: Wenn Person hinzugefügt wird, wird Funktion in dieser Klasse aufgerufen
        connect(neuesFenster, &Fenster1::personHinzugefuegt, this, &ausgabetabelle::fuegePersonHinzu);
        neuesFenster->show();
    });
}


ausgabetabelle::~ausgabetabelle() {}

// Übergibt neue Personendaten und aktualisiert die Tabelle
void ausgabetabelle::setPersonen(const std::vector<Person>& neuePersonen) {
    personen = neuePersonen;
    aktualisiereTabelle();
}

// Aktualisiert die Tabelle mit aktuellen Personendaten
void ausgabetabelle::aktualisiereTabelle() {
    tableWidget->setRowCount(static_cast<int>(personen.size()));

    for (int i = 0; i < static_cast<int>(personen.size()); ++i) {
        // Checkbox in erster Spalte einfügen
        QWidget *checkBoxWidget = new QWidget();
        QCheckBox *checkBox = new QCheckBox();
        QHBoxLayout *layoutCheck = new QHBoxLayout(checkBoxWidget);
        layoutCheck->addWidget(checkBox);
        layoutCheck->setAlignment(Qt::AlignCenter);
        layoutCheck->setContentsMargins(0, 0, 0, 0);
        checkBoxWidget->setLayout(layoutCheck);
        tableWidget->setCellWidget(i, 0, checkBoxWidget);

        // Name und Alter setzen
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(personen[i].getName())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(personen[i].getAge())));
    }
}

// Nicht verwendete Methode (wird durch den Button-Handler ersetzt)
void ausgabetabelle::loescheAusgewaehlteZeilen() {
    for (int i = tableWidget->rowCount() - 1; i >= 0; --i) {
        QWidget *widget = tableWidget->cellWidget(i, 0);
        if (!widget) continue;

        QCheckBox *checkBox = widget->findChild<QCheckBox *>();
        if (checkBox && checkBox->isChecked()) {
            tableWidget->removeRow(i);
        }
    }
}

// Fügt eine neue Person hinzu (von Fenster1 empfangen)
void ausgabetabelle::fuegePersonHinzu(const QString &name, int alter) {
    // Neue Person im Vektor speichern
    personen.emplace_back(name.toStdString(), alter);

    // Neue Zeile in Tabelle einfügen
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    QWidget *checkBoxWidget = new QWidget();
    QCheckBox *checkBox = new QCheckBox();
    QHBoxLayout *layoutCheck = new QHBoxLayout(checkBoxWidget);
    layoutCheck->addWidget(checkBox);
    layoutCheck->setAlignment(Qt::AlignCenter);
    layoutCheck->setContentsMargins(0, 0, 0, 0);
    checkBoxWidget->setLayout(layoutCheck);
    tableWidget->setCellWidget(row, 0, checkBoxWidget);

    // Name und Alter in neuer Zeile einfügen
    tableWidget->setItem(row, 1, new QTableWidgetItem(name));
    tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(alter)));

    // Datei nach Hinzufügen direkt aktualisieren
    Datenbank::schreibePersonenInDatei(personen);
}

// Einfaches Fenster öffnen (nicht weiter verwendet aktuell)
void ausgabetabelle::oeffneNeuesFenster() {
    QWidget *fenster = new QWidget();
    fenster->setWindowTitle("Neues Fenster");
    fenster->resize(300, 200);
    fenster->show();
}
