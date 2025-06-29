#include "eingabe.h"
#include "medium.h"
#include "book.h"
#include "BlueRay.h"
#include "datenbank.h"
#include "fenster2.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QMessageBox>
#include <algorithm>
#include <QHeaderView>


eingabe::eingabe(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Medientabelle");

    auto *mainLayout = new QVBoxLayout(this);

    // Tabelle mit 4 Spalten: Checkbox, Titel, Typ, ID (z.B. ISBN/Fsk)
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "" << "Titel" << "Autor/Regisseur" << "ISBN/FSK" << "Ausgeliehen");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLayout->addWidget(tableWidget);

    // Buttons erstellen
    btnSpeichern = new QPushButton("Speichern", this);
    btnLoeschen = new QPushButton("Ausgewählte löschen", this);
    btnHinzufuegen = new QPushButton("Neuhinzufügen", this);

    mainLayout->addWidget(btnSpeichern);
    mainLayout->addWidget(btnLoeschen);
    mainLayout->addWidget(btnHinzufuegen);

    setLayout(mainLayout);

    // Medien initial laden
    medien = Datenbank::leseMedienAusDatei("../mediumDb.txt");
    aktualisiereTabelle();

    connect(btnSpeichern, &QPushButton::clicked, this, &eingabe::speichereMedien);

    connect(btnLoeschen, &QPushButton::clicked, this, &eingabe::loescheAusgewaehlteZeilen);

    connect(btnHinzufuegen, &QPushButton::clicked, this, [this]() {
        Fenster2 *fenster = new Fenster2(nullptr);
        connect(fenster, &Fenster2::mediumHinzugefuegt, this, &eingabe::fuegeMediumHinzu);
        fenster->show();
    });
}

eingabe::~eingabe() {
    for (auto m : medien) {
        delete m;
    }
}

void eingabe::aktualisiereTabelle() {
    tableWidget->setRowCount(static_cast<int>(medien.size()));
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "" << "Titel" << "Autor/Regisseur" << "ISBN/FSK" << "Ausgeliehen");

    for (int i = 0; i < static_cast<int>(medien.size()); ++i) {
        // Checkbox
        QWidget *checkBoxWidget = new QWidget();
        QCheckBox *checkBox = new QCheckBox();
        QHBoxLayout *layoutCheck = new QHBoxLayout(checkBoxWidget);
        layoutCheck->addWidget(checkBox);
        layoutCheck->setAlignment(Qt::AlignCenter);
        layoutCheck->setContentsMargins(0, 0, 0, 0);
        checkBoxWidget->setLayout(layoutCheck);
        tableWidget->setCellWidget(i, 0, checkBoxWidget);

        // Titel
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(medien[i]->getTitle())));

        // Autor/Regisseur, ISBN/FSK, Ausgeliehen
        QString personStr = "n/a";
        QString idStr = "n/a";
        QString ausgeliehenStr = "Nein";

        if (medien[i]->gettype() == "Book") {
            auto buch = dynamic_cast<book*>(medien[i]);
            if (buch) {
                personStr = QString::fromStdString(buch->getAuthor());
                idStr = QString::fromStdString(buch->getISBN());
                ausgeliehenStr = buch->getAusgeliehen() ? "Ja" : "Nein";
            }
        } else if (medien[i]->gettype() == "BlueRay") {
            auto br = dynamic_cast<BlueRay*>(medien[i]);
            if (br) {
                personStr = QString::fromStdString(br->getDirector());
                idStr = QString::number(br->getFSK());
                ausgeliehenStr = br->getAusgeliehen() ? "Ja" : "Nein";
            }
        }

        tableWidget->setItem(i, 2, new QTableWidgetItem(personStr));
        tableWidget->setItem(i, 3, new QTableWidgetItem(idStr));
        tableWidget->setItem(i, 4, new QTableWidgetItem(ausgeliehenStr));
    }
}


void eingabe::loescheAusgewaehlteZeilen() {
    std::vector<int> zeilenZuLoeschen;
    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        QWidget* widget = tableWidget->cellWidget(i, 0);
        if (widget) {
            QCheckBox* cb = widget->findChild<QCheckBox*>();
            if (cb && cb->isChecked())
                zeilenZuLoeschen.push_back(i);
        }
    }

    std::sort(zeilenZuLoeschen.rbegin(), zeilenZuLoeschen.rend());

    Datenbank::loescheMedien(medien, zeilenZuLoeschen);

    for (int idx : zeilenZuLoeschen)
        tableWidget->removeRow(idx);

    speichereMedien();
}

void eingabe::fuegeMediumHinzu(const QString &titel, const QString &person, const QString &id, const QString &typ)
{
    Medium* neu = nullptr;

    if (typ == "Book") {
        neu = new book(titel.toStdString(), person.toStdString(), id.toStdString());
    } else if (typ == "BlueRay") {
        bool ok;
        int fsk = id.toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Fehler", "FSK muss eine Zahl sein!");
            return;
        }
        neu = new BlueRay(titel.toStdString(), person.toStdString(), fsk);
    } else {
        QMessageBox::warning(this, "Fehler", "Unbekannter Medientyp!");
        return;
    }

    neu->setAusgeliehen(false);  // Neu hinzugefügte Medien sind nicht ausgeliehen

    medien.push_back(neu);

    // Neue Zeile in Tabelle hinzufügen
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

    tableWidget->setItem(row, 1, new QTableWidgetItem(titel));
    tableWidget->setItem(row, 2, new QTableWidgetItem(person));
    tableWidget->setItem(row, 3, new QTableWidgetItem(id));
    tableWidget->setItem(row, 4, new QTableWidgetItem("Nein"));  // Ausgeliehen = Nein

    speichereMedien();  // Daten in Datei speichern
}



void eingabe::speichereMedien() {
    if (Datenbank::schreibeMedienInDatei(medien, "../mediumDb.txt")) {
        QMessageBox::information(this, "Erfolg", "Medien gespeichert.");
    } else {
        QMessageBox::warning(this, "Fehler", "Speichern fehlgeschlagen.");
    }
}
