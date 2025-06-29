#include "ausleihanzeige.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>

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
    connect(addButton, &QPushButton::clicked, this, &AusleihAnzeige::hinzufuegenClicked);
    connect(deleteButton, &QPushButton::clicked, this, &AusleihAnzeige::loeschenClicked);
}

void AusleihAnzeige::setAusleihen(const std::vector<Ausleihe> &ausleihen,
                                   const std::vector<Person> &personen,
                                   const std::vector<Medium> &medien)
{
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

        for (const auto& medium : medien) {
            if (medium.getId() == ausleihe.mediumId) {
                mediumTitle = QString::fromStdString(medium.getTitle());
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

std::vector<int> AusleihAnzeige::getAusgewaehlteZeilen() const
{
    std::vector<int> ausgewaehlt;
    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        QTableWidgetItem *item = tableWidget->item(i, 0);
        if (item && item->checkState() == Qt::Checked) {
            ausgewaehlt.push_back(i);
        }
    }
    return ausgewaehlt;
}
