#include "ausleihanzeige.h"
#include "ausleihdialog.h"
#include "datenbank.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QDebug>

AusleihAnzeige::AusleihAnzeige(QWidget *parent)
    : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    auto *buttonLayout = new QHBoxLayout();

    // Tabelle einrichten
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3); // Checkbox + Person + Medium
    tableWidget->setHorizontalHeaderLabels(QStringList() << "" << "Person" << "Medium");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Buttons erstellen
    addButton = new QPushButton("Hinzufügen", this);
    deleteButton = new QPushButton("Löschen", this);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(tableWidget);

    // Signale verbinden
    connect(addButton, &QPushButton::clicked, this, [this]() {
        if (personen.empty() || medien.empty()) return;

        AusleihDialog dialog(medien, personen, this);
        if (dialog.exec() == QDialog::Accepted) {
            int personId = dialog.getSelectedPersonId();
            int mediumId = dialog.getSelectedMediumId();

            // IDs prüfen
            bool validPerson = std::any_of(personen.begin(), personen.end(), [personId](const Person& p){ return p.getId() == personId; });
            bool validMedium = std::any_of(medien.begin(), medien.end(), [mediumId](const Medium* m){ return m->getId() == mediumId; });

            if (!validPerson || !validMedium) {
                QMessageBox::warning(this, "Fehler", "Ungültige Person oder Medium ausgewählt!");
                qDebug() << "Ungültige IDs: personId =" << personId << ", mediumId =" << mediumId;
                return;
            }

            qDebug() << "Hinzufügen: personId =" << personId << ", mediumId =" << mediumId;

            // 1. Ausleihe zur Liste hinzufügen
            AusleihManager::fuegeAusleiheHinzu(aktuelleAusleihen, personId, mediumId);

            // 2. Medium auf "ausgeliehen = true" setzen
            for (auto* m : medien) {
                if (m->getId() == mediumId) {
                    m->setAusgeliehen(true);
                    break;
                }
            }

            // 3. Dateien speichern
            AusleihManager::speichereAusleihenInDatei(aktuelleAusleihen, AusleihManager::DATEIPFAD);
            Datenbank::schreibeMedienInDatei(medien, "medien.txt");  // Passe den Dateinamen ggf. an

            // 4. Anzeige aktualisieren
            setAusleihen(aktuelleAusleihen, personen, medien);
        }
    });

    
}

void AusleihAnzeige::setAusleihen(const std::vector<Ausleihe> &ausleihen,
    const std::vector<Person> &personen,
    const std::vector<Medium*> &medien)
{
this->aktuelleAusleihen = ausleihen;
this->personen = personen;
this->medien = medien;

tableWidget->clearContents();
tableWidget->setRowCount(static_cast<int>(ausleihen.size()));
tableWidget->setColumnCount(3);
tableWidget->setHorizontalHeaderLabels(QStringList() << "" << "Person" << "Medium");

for (int i = 0; i < static_cast<int>(ausleihen.size()); ++i) {
const Ausleihe& ausleihe = ausleihen[i];

QString personName = "Unbekannt";
QString mediumTitle = "Unbekannt";

for (const auto& person : personen) {
if (person.getId() == ausleihe.personenId) {
personName = QString::fromStdString(person.getName());
break;
}
}

for (const auto* medium : medien) {
if (medium->getId() == ausleihe.mediumId) {
mediumTitle = QString::fromStdString(medium->getTitle());
break;
}
}

// Checkbox-Spalte
auto *checkItem = new QTableWidgetItem();
checkItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
checkItem->setCheckState(Qt::Unchecked);
tableWidget->setItem(i, 0, checkItem);

// Person und Medium
tableWidget->setItem(i, 1, new QTableWidgetItem(personName));
tableWidget->setItem(i, 2, new QTableWidgetItem(mediumTitle));
}

tableWidget->resizeColumnsToContents();
}

