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

ausgabetabelle::ausgabetabelle(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Ausgabetabelle");

    auto *mainLayout = new QVBoxLayout(this);

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3);  // Checkbox, Name, Alter
    tableWidget->setHorizontalHeaderLabels(QStringList() << "" << "Name" << "Alter");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLayout->addWidget(tableWidget);

    btnSpeichern = new QPushButton("Speichern", this);
    btnLoeschen = new QPushButton("Ausgewählte löschen", this);
    neuhinzufügen = new QPushButton("Neuhinzufügen", this);

    mainLayout->addWidget(btnSpeichern);
    mainLayout->addWidget(btnLoeschen);
    mainLayout->addWidget(neuhinzufügen);

    setLayout(mainLayout);

    connect(btnSpeichern, &QPushButton::clicked, this, [this]() {
        if (Datenbank::schreibePersonenInDatei(personen)) {
            QMessageBox::information(this, "Erfolg", "Datei gespeichert.");
        } else {
            QMessageBox::warning(this, "Fehler", "Datei konnte nicht gespeichert werden.");
        }
    });

    connect(btnLoeschen, &QPushButton::clicked, this, [this]() {
        std::vector<int> zeilenZuLoeschen;
        for (int i = 0; i < tableWidget->rowCount(); ++i) {
            QWidget* widget = tableWidget->cellWidget(i, 0);
            if (widget) {
                QCheckBox* cb = widget->findChild<QCheckBox*>();
                if (cb && cb->isChecked())
                    zeilenZuLoeschen.push_back(i);
            }
        }

        // Sortieren absteigend
        std::sort(zeilenZuLoeschen.rbegin(), zeilenZuLoeschen.rend());

        Datenbank::loeschePersonen(personen, zeilenZuLoeschen);

        for (int idx : zeilenZuLoeschen)
            tableWidget->removeRow(idx);

        Datenbank::schreibePersonenInDatei(personen);
    });

    connect(neuhinzufügen, &QPushButton::clicked, this, [this]() {
        Fenster1 *neuesFenster = new Fenster1();
        connect(neuesFenster, &Fenster1::personHinzugefuegt, this, &ausgabetabelle::fuegePersonHinzu);
        neuesFenster->show();
    });
}

ausgabetabelle::~ausgabetabelle() {}

void ausgabetabelle::setPersonen(const std::vector<Person>& neuePersonen) {
    personen = neuePersonen;
    aktualisiereTabelle();
}

void ausgabetabelle::aktualisiereTabelle() {
    tableWidget->setRowCount(static_cast<int>(personen.size()));

    for (int i = 0; i < static_cast<int>(personen.size()); ++i) {
        QWidget *checkBoxWidget = new QWidget();
        QCheckBox *checkBox = new QCheckBox();
        QHBoxLayout *layoutCheck = new QHBoxLayout(checkBoxWidget);
        layoutCheck->addWidget(checkBox);
        layoutCheck->setAlignment(Qt::AlignCenter);
        layoutCheck->setContentsMargins(0, 0, 0, 0);
        checkBoxWidget->setLayout(layoutCheck);
        tableWidget->setCellWidget(i, 0, checkBoxWidget);

        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(personen[i].getName())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(personen[i].getAge())));
    }
}

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

void ausgabetabelle::fuegePersonHinzu(const QString &name, int alter) {
    personen.emplace_back(name.toStdString(), alter);

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

    tableWidget->setItem(row, 1, new QTableWidgetItem(name));
    tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(alter)));

    Datenbank::schreibePersonenInDatei(personen);
}

void ausgabetabelle::oeffneNeuesFenster() {
    QWidget *fenster = new QWidget();
    fenster->setWindowTitle("Neues Fenster");
    fenster->resize(300, 200);
    fenster->show();
}
