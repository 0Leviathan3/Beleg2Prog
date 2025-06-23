#include "ausgabetabelle.h"
#include "book.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <algorithm>

eingabe::eingabe(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Medientabelle");

    auto *mainLayout = new QVBoxLayout(this);

    // Tabelle vorbereiten (4 Spalten: Checkbox, Titel, Typ, ID)
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "" << "Titel" << "Typ" << "ID");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLayout->addWidget(tableWidget);

    // Buttons
    btnSpeichern = new QPushButton("Speichern", this); // Optional
    btnLoeschen = new QPushButton("Ausgewählte löschen", this);
    btnHinzufuegen = new QPushButton("Medium hinzufügen", this);

    mainLayout->addWidget(btnSpeichern);
    mainLayout->addWidget(btnLoeschen);
    mainLayout->addWidget(btnHinzufuegen);

    setLayout(mainLayout);

    // Event-Verbindungen
    connect(btnLoeschen, &QPushButton::clicked, this, &eingabe::loescheAusgewaehlteZeilen);
    connect(btnHinzufuegen, &QPushButton::clicked, this, &eingabe::fuegeMediumHinzu);
    connect(btnSpeichern, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Hinweis", "Speichern der Medien könnte hier implementiert werden.");
    });
}

eingabe::~eingabe() {
    for (Medium* m : medien)
        delete m;
}

void eingabe::setMedien(const std::vector<Medium*>& neueMedien) {
    // alte löschen
    for (Medium* m : medien)
        delete m;
    medien = neueMedien;
    aktualisiereTabelle();
}

void eingabe::aktualisiereTabelle() {
    tableWidget->setRowCount(static_cast<int>(medien.size()));

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

        // Medium-Daten
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(medien[i]->getTitle())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(medien[i]->gettype())));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(medien[i]->getId())));
    }
}

void eingabe::loescheAusgewaehlteZeilen() {
    std::vector<int> zuLoeschen;
    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        QWidget *widget = tableWidget->cellWidget(i, 0);
        if (!widget) continue;
        QCheckBox *checkBox = widget->findChild<QCheckBox *>();
        if (checkBox && checkBox->isChecked()) {
            zuLoeschen.push_back(i);
        }
    }

    std::sort(zuLoeschen.rbegin(), zuLoeschen.rend()); // von unten löschen
    for (int row : zuLoeschen) {
        delete medien[row];
        medien.erase(medien.begin() + row);
        tableWidget->removeRow(row);
    }
}

void eingabe::fuegeMediumHinzu() {
    // Beispiel: Dummy-Book hinzufügen
    auto* neuesBuch = new book("Neuer Titel", 123456, "Autor XY");
    medien.push_back(neuesBuch);
    aktualisiereTabelle();
}
