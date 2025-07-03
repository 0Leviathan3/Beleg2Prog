#include "ausleihanzeige.h"
#include "ausleihdialog.h"
#include "datenbank.h"
#include "ausleihmanager.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>

AusleihAnzeige::AusleihAnzeige(QWidget *parent)
    : QWidget(parent)
{
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels({"Person", "Medium"});
    tableWidget->horizontalHeader()->setStretchLastSection(true);

    addButton = new QPushButton("Hinzufügen", this);
    deleteButton = new QPushButton("Entfernen", this);

    connect(addButton, &QPushButton::clicked, this, [=]() {
        AusleihDialog dialog(personen, medien, this);
        if (dialog.exec() == QDialog::Accepted) {
            std::vector<std::string> selectedPersonNamen = dialog.getAusgewaehltePersonen();
            std::string selectedMediumTitel = dialog.getAusgewaehltesMedium();

            for (const std::string &name : selectedPersonNamen) {
                AusleihManager::fuegeAusleiheHinzu(aktuelleAusleihen, name, selectedMediumTitel);
            }

            if (AusleihManager::speichereAusleihenInDatei(aktuelleAusleihen, "../ausleihen.txt")) {
                setAusleihen(aktuelleAusleihen, personenObjekte, medien);  // Hier jetzt personenObjekte als const std::vector<Person>&
            } else {
                QMessageBox::warning(this, "Fehler", "Speichern der Ausleihen fehlgeschlagen.");
            }
        }
    });

    connect(deleteButton, &QPushButton::clicked, this, [=]() {
        std::vector<int> zeilen = getAusgewaehlteZeilen();
        for (int i = zeilen.size() - 1; i >= 0; --i) {
            QString person = tableWidget->item(zeilen[i], 0)->text();
            QString medium = tableWidget->item(zeilen[i], 1)->text();
            AusleihManager::entferneAusleihe(aktuelleAusleihen, person.toStdString(), medium.toStdString());
        }

        if (AusleihManager::speichereAusleihenInDatei(aktuelleAusleihen, "../ausleihen.txt")) {
            setAusleihen(aktuelleAusleihen, personenObjekte, medien);
        } else {
            QMessageBox::warning(this, "Fehler", "Speichern der Ausleihen fehlgeschlagen.");
        }
    });

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

// Nehme an, du hast irgendwo einen Vektor mit Person-Objekten
// Den brauchst du, um aus ihm die Zeiger für 'personen' zu bauen
// Zum Beispiel in der Header-Datei:
// std::vector<Person> personenObjekte;

void AusleihAnzeige::setAusleihen(const std::vector<Ausleihe> &ausleihen,
                                  const std::vector<Person> &personenObjekte,
                                  const std::vector<Medium*> &medien)
{
    this->aktuelleAusleihen = ausleihen;
    this->medien = medien;

    // Personen-Zeiger aktualisieren
    personen.clear();
    for (const Person &p : personenObjekte) {
        personen.push_back(const_cast<Person*>(&p));
    }

    tableWidget->setRowCount(0);
    for (const Ausleihe &ausleihe : ausleihen) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(ausleihe.personenName)));
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(ausleihe.mediumTitel)));
    }
}

std::vector<int> AusleihAnzeige::getAusgewaehlteZeilen() const
{
    std::vector<int> zeilen;
    QList<QTableWidgetItem*> selectedItems = tableWidget->selectedItems();
    for (QTableWidgetItem *item : selectedItems) {
        int row = item->row();
        if (std::find(zeilen.begin(), zeilen.end(), row) == zeilen.end())
            zeilen.push_back(row);
    }
    return zeilen;
}
