#include "ausleihdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include "ausleihmanager.h"
#include <QMessageBox>

AuswahlDialog::AuswahlDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Medium/Person Auswahl");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    stackedWidget = new QStackedWidget(this);

    // --- Medien laden ---
    Datenbank db;
    medien = db.leseMedienAusDatei("../mediumDb.txt");

    medienTabelle = new QTableWidget(this);
    medienTabelle->setColumnCount(1);
    medienTabelle->setHorizontalHeaderLabels(QStringList() << "Titel");
    medienTabelle->horizontalHeader()->setStretchLastSection(true);
    medienTabelle->setSelectionBehavior(QAbstractItemView::SelectRows);
    medienTabelle->setSelectionMode(QAbstractItemView::SingleSelection);
    medienTabelle->setRowCount(static_cast<int>(medien.size()));

    for (int i = 0; i < static_cast<int>(medien.size()); ++i) {
        medienTabelle->setItem(i, 0, new QTableWidgetItem(
            QString::fromStdString(medien[i]->getTitle())));
    }

    stackedWidget->addWidget(medienTabelle);

    // --- Personen-Tabelle vorbereiten (leer initial) ---
    personenTabelle = new QTableWidget(this);
    personenTabelle->setColumnCount(2);
    personenTabelle->setHorizontalHeaderLabels(QStringList() << "Name" << "Alter");
    personenTabelle->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    personenTabelle->setSelectionBehavior(QAbstractItemView::SelectRows);
    personenTabelle->setSelectionMode(QAbstractItemView::SingleSelection);
    personenTabelle->setEditTriggers(QAbstractItemView::NoEditTriggers);

    stackedWidget->addWidget(personenTabelle);

    // --- Buttons ---
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    weiterButton = new QPushButton("Weiter", this);
    bestaetigenButton = new QPushButton("Fertig", this);

    buttonLayout->addStretch();
    buttonLayout->addWidget(weiterButton);
    buttonLayout->addWidget(bestaetigenButton);

    // --- Verbindungen ---
    connect(weiterButton, &QPushButton::clicked, this, &AuswahlDialog::weiter);
    connect(bestaetigenButton, &QPushButton::clicked, this, &AuswahlDialog::bestaetigen);

    mainLayout->addWidget(stackedWidget);
    mainLayout->addLayout(buttonLayout);
}

void AuswahlDialog::weiter()
{
    // Ausgewähltes Medium speichern
    auto items = medienTabelle->selectedItems();
    if (!items.empty()) {
        int row = medienTabelle->row(items[0]);
        ausgewaehltesMedium = medien[row];
    } else {
        // Falls nichts gewählt, Medium auf nullptr setzen
        ausgewaehltesMedium = nullptr;
    }

    // Personen laden
    Datenbank db;
    personen = db.lesePersonenAusDatei("../beispiel.txt");

    personenTabelle->setRowCount(static_cast<int>(personen.size()));

    for (int i = 0; i < static_cast<int>(personen.size()); ++i) {
        personenTabelle->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(personen[i].getName())));
        personenTabelle->setItem(i, 1, new QTableWidgetItem(QString::number(personen[i].getAge())));
    }

    // Zur Personen-Ansicht wechseln
    stackedWidget->setCurrentWidget(personenTabelle);
}

Medium* AuswahlDialog::getAusgewaehltesMedium() const
{
    return ausgewaehltesMedium;
}

Person AuswahlDialog::getAusgewaehltePerson() const
{
    return ausgewaehltePerson;
}
void AuswahlDialog::bestaetigen()
{
    // Ausgewählte Person speichern
    auto items = personenTabelle->selectedItems();
    if (!items.empty()) {
        int row = personenTabelle->row(items[0]);
        ausgewaehltePerson = personen[row];
    } else {
        ausgewaehltePerson = Person();
    }

    if (ausgewaehltesMedium && !ausgewaehltePerson.getName().empty()) {
        std::vector<Ausleihe> ausleihen = AusleihManager::ladeAusleihenAusDatei("../ausleihen.txt");

        // Prüfen, ob Medium bereits ausgeliehen ist
        if (AusleihManager::istMediumAusgeliehen(ausleihen, ausgewaehltesMedium->getTitle())) {
            QMessageBox::warning(this, "Fehler", "Dieses Medium ist bereits ausgeliehen.");
            return; // nicht weitermachen
        }

        // Medium ausleihen (Hinzufügen)
        AusleihManager::fuegeAusleiheHinzu(
            ausleihen,
            ausgewaehltePerson.getName(),
            ausgewaehltesMedium->getTitle());

        // Änderungen speichern
        bool success = AusleihManager::speichereAusleihenInDatei(ausleihen, "../ausleihen.txt");

        if (success) {
            QMessageBox::information(this, "Erfolg", "Ausleihe wurde gespeichert.");
            accept(); // Dialog schließen
        } else {
            QMessageBox::warning(this, "Fehler", "Fehler beim Speichern der Ausleihe.");
        }
    } else {
        QMessageBox::warning(this, "Fehler", "Bitte Medium und Person auswählen.");
    }
}
