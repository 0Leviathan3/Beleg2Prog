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
    auto *mainLayout = new QVBoxLayout(this);
    auto *buttonLayout = new QHBoxLayout();

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3); // Checkbox + Person + Medium
    tableWidget->setHorizontalHeaderLabels(QStringList() << "" << "Person" << "Medium");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    addButton = new QPushButton("Hinzufügen", this);
    deleteButton = new QPushButton("Löschen", this);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(tableWidget);

    connect(addButton, &QPushButton::clicked, this, [this]() {
        AusleihDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            std::vector<std::string> personNamen = dialog.getSelectedPersonNames();
            std::string mediumTitel = dialog.getSelectedMediumTitle();

            if (personNamen.empty()) {
                QMessageBox::warning(this, "Ausleihe", "Keine Personen ausgewählt.");
                return;
            }

            if (AusleihManager::istMediumAusgeliehen(this->aktuelleAusleihen, mediumTitel)) {
                QMessageBox::warning(this, "Ausleihe", "Das Medium ist bereits ausgeliehen!");
                return;
            }

            for (const auto& name : personNamen) {
                AusleihManager::fuegeAusleiheHinzu(this->aktuelleAusleihen, name, mediumTitel);
            }

            for (auto* medium : this->medien) {
                if (medium->getTitle() == mediumTitel) {
                    medium->setAusgeliehen(true);
                    break;
                }
            }

            AusleihManager::speichereAusleihenInDatei(this->aktuelleAusleihen, "../ausleihen.txt");
            Datenbank::schreibeMedienInDatei(this->medien, "../medien.txt");

            this->personen = Datenbank::lesePersonenAusDatei("../beispiel.txt");

            this->setAusleihen(this->aktuelleAusleihen, this->personen, this->medien);
        }
    });

    // TODO: deleteButton mit Lösch-Logik verbinden
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

        QString personName = QString::fromStdString(ausleihe.personenName);
        QString mediumTitle = QString::fromStdString(ausleihe.mediumTitel);

        auto *checkItem = new QTableWidgetItem();
        checkItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        checkItem->setCheckState(Qt::Unchecked);
        tableWidget->setItem(i, 0, checkItem);

        tableWidget->setItem(i, 1, new QTableWidgetItem(personName));
        tableWidget->setItem(i, 2, new QTableWidgetItem(mediumTitle));
    }

    tableWidget->resizeColumnsToContents();
}

std::vector<int> AusleihAnzeige::getAusgewaehlteZeilen() const
{
    std::vector<int> ausgewaehlteZeilen;

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        auto *item = tableWidget->item(row, 0);
        if (item && item->checkState() == Qt::Checked) {
            ausgewaehlteZeilen.push_back(row);
        }
    }

    return ausgewaehlteZeilen;
}
