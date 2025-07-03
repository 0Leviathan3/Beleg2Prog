#include "ausleihdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>

AusleihDialog::AusleihDialog(const std::vector<Person*>& personen,
                             const std::vector<Medium*>& medien,
                             QWidget *parent)
    : QDialog(parent),
      selectedPersonNamen(),
      selectedMediumTitel()
{
    setWindowTitle("Ausleih-Dialog");

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // StackedWidget, das zwischen Personen- und Medien-Tabelle wechselt
    stackedWidget = new QStackedWidget(this);

    // Personen-Tabelle
    personenTabelle = new QTableWidget(this);
    personenTabelle->setColumnCount(1);
    personenTabelle->setHorizontalHeaderLabels(QStringList() << "Person");
    personenTabelle->horizontalHeader()->setStretchLastSection(true);
    personenTabelle->setSelectionBehavior(QAbstractItemView::SelectRows);
    personenTabelle->setSelectionMode(QAbstractItemView::SingleSelection);
    personenTabelle->setRowCount(static_cast<int>(personen.size()));

    for (int i = 0; i < static_cast<int>(personen.size()); ++i) {
        personenTabelle->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(personen[i]->getName())));
    }

    // Medien-Tabelle
    medienTabelle = new QTableWidget(this);
    medienTabelle->setColumnCount(1);
    medienTabelle->setHorizontalHeaderLabels(QStringList() << "Medium");
    medienTabelle->horizontalHeader()->setStretchLastSection(true);
    medienTabelle->setSelectionBehavior(QAbstractItemView::SelectRows);
    medienTabelle->setSelectionMode(QAbstractItemView::SingleSelection);
    medienTabelle->setRowCount(static_cast<int>(medien.size()));

    for (int i = 0; i < static_cast<int>(medien.size()); ++i) {
        medienTabelle->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(medien[i]->getTitle())));
    }

    // Dem StackedWidget hinzufügen
    stackedWidget->addWidget(personenTabelle);
    stackedWidget->addWidget(medienTabelle);

    mainLayout->addWidget(stackedWidget);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *naechsterButton = new QPushButton("Nächster", this);
    QPushButton *bestaetigenButton = new QPushButton("Bestätigen", this);
    QPushButton *abbrechenButton = new QPushButton("Abbrechen", this);

    buttonLayout->addWidget(naechsterButton);
    buttonLayout->addWidget(bestaetigenButton);
    buttonLayout->addWidget(abbrechenButton);

    mainLayout->addLayout(buttonLayout);

    // Verbindungen
    connect(naechsterButton, &QPushButton::clicked, this, [this]() {
        int currentIndex = stackedWidget->currentIndex();
        if (currentIndex < stackedWidget->count() - 1) {
            stackedWidget->setCurrentIndex(currentIndex + 1);
        }
    });

    connect(bestaetigenButton, &QPushButton::clicked, this, &AusleihDialog::bestaetigen);
    connect(abbrechenButton, &QPushButton::clicked, this, &AusleihDialog::reject);
}

void AusleihDialog::bestaetigen()
{
    // Ausgewählte Person speichern
    auto personItems = personenTabelle->selectedItems();
    selectedPersonNamen.clear();
    if (!personItems.empty()) {
        selectedPersonNamen.push_back(personItems[0]->text().toStdString());
    }

    // Ausgewähltes Medium speichern
    auto mediumItems = medienTabelle->selectedItems();
    selectedMediumTitel.clear();
    if (!mediumItems.empty()) {
        selectedMediumTitel = mediumItems[0]->text().toStdString();
    }

    accept();
}

std::vector<std::string> AusleihDialog::getAusgewaehltePersonen() const
{
    return selectedPersonNamen;
}

std::string AusleihDialog::getAusgewaehltesMedium() const
{
    return selectedMediumTitel;
}
