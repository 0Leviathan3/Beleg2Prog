#include "ausleihdialog.h"
#include "datenbank.h"
#include "ausleihmanager.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>

AusleihDialog::AusleihDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Ausleihe hinzufügen");
    resize(400, 300);

    allePersonen = Datenbank::lesePersonenAusDatei("../beispiel.txt");
    alleMedien = Datenbank::leseMedienAusDatei("../mediumDb.txt");

    auto ausleihen = AusleihManager::ladeAusleihenAusDatei("../ausleihen.txt");
    for (auto* m : alleMedien) {
        if (!AusleihManager::istMediumAusgeliehen(ausleihen, m->getTitle())) {
            verfuegbareMedien.push_back(m);
        }
    }

    auto *mainLayout = new QVBoxLayout(this);
    stack = new QStackedWidget(this);
    mainLayout->addWidget(stack);

    erzeugePersonenTabelle();
    erzeugeMedienAuswahl();

    stack->setCurrentIndex(0);
}

void AusleihDialog::erzeugePersonenTabelle() {
    QWidget *seite = new QWidget(this);
    auto *layout = new QVBoxLayout(seite);

    layout->addWidget(new QLabel("Person auswählen:"));

    personenTabelle = new QTableWidget(this);
    personenTabelle->setColumnCount(2);
    personenTabelle->setHorizontalHeaderLabels(QStringList() << "Name" << "Alter");
    personenTabelle->setSelectionBehavior(QAbstractItemView::SelectRows);
    personenTabelle->setSelectionMode(QAbstractItemView::MultiSelection);
    personenTabelle->setEditTriggers(QAbstractItemView::NoEditTriggers);
    personenTabelle->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    personenTabelle->setRowCount(static_cast<int>(allePersonen.size()));
    for (int i = 0; i < static_cast<int>(allePersonen.size()); ++i) {
        personenTabelle->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(allePersonen[i].getName())));
        personenTabelle->setItem(i, 1, new QTableWidgetItem(QString::number(allePersonen[i].getAge())));
    }
    layout->addWidget(personenTabelle);

    weiterButton = new QPushButton("Weiter zu Medienauswahl", this);
    layout->addWidget(weiterButton);

    connect(weiterButton, &QPushButton::clicked, this, &AusleihDialog::geheZuMedienAuswahl);

    stack->addWidget(seite);
}

void AusleihDialog::erzeugeMedienAuswahl() {
    QWidget *seite = new QWidget(this);
    auto *layout = new QVBoxLayout(seite);

    layout->addWidget(new QLabel("Medium auswählen:"));

    medienTabelle = new QTableWidget(this);
    medienTabelle->setColumnCount(2);
    medienTabelle->setHorizontalHeaderLabels(QStringList() << "Titel" << "Typ");
    medienTabelle->setSelectionBehavior(QAbstractItemView::SelectRows);
    medienTabelle->setSelectionMode(QAbstractItemView::SingleSelection);
    medienTabelle->setEditTriggers(QAbstractItemView::NoEditTriggers);
    medienTabelle->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    medienTabelle->setRowCount(static_cast<int>(verfuegbareMedien.size()));
    for (int i = 0; i < static_cast<int>(verfuegbareMedien.size()); ++i) {
        Medium* m = verfuegbareMedien[i];
        medienTabelle->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(m->getTitle())));
        medienTabelle->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(m->gettype())));
    }
    layout->addWidget(medienTabelle);

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();

    ausleihenButton = new QPushButton("Ausleihen", this);
    buttonLayout->addWidget(ausleihenButton);

    layout->addLayout(buttonLayout);

    connect(ausleihenButton, &QPushButton::clicked, this, &AusleihDialog::ausleihen);

    stack->addWidget(seite);
}

void AusleihDialog::geheZuMedienAuswahl() {
    selectedPersonNames.clear();

    auto selectedRanges = personenTabelle->selectionModel()->selectedRows();

    if (selectedRanges.isEmpty()) {
        QMessageBox::warning(this, "Fehler", "Bitte wähle mindestens eine Person aus.");
        return;
    }

    for (const QModelIndex &index : selectedRanges) {
        int row = index.row();
        if (row >= 0 && row < static_cast<int>(allePersonen.size())) {
            selectedPersonNames.push_back(allePersonen[row].getName());
        }
    }

    stack->setCurrentIndex(1);
}

void AusleihDialog::ausleihen() {
    if (selectedPersonNames.empty()) {
        QMessageBox::warning(this, "Fehler", "Keine Person(en) ausgewählt.");
        return;
    }

    auto selectedRanges = medienTabelle->selectionModel()->selectedRows();
    if (selectedRanges.isEmpty()) {
        QMessageBox::warning(this, "Fehler", "Kein Medium ausgewählt.");
        return;
    }

    int row = selectedRanges.first().row();
    if (row < 0 || row >= static_cast<int>(verfuegbareMedien.size())) {
        QMessageBox::warning(this, "Fehler", "Ungültige Medium-Auswahl.");
        return;
    }

    selectedMediumTitle = verfuegbareMedien[row]->getTitle();

    // Lade aktuelle Ausleihen
    auto ausleihen = AusleihManager::ladeAusleihenAusDatei("../ausleihen.txt");

    // Prüfen ob Medium bereits ausgeliehen ist
    if (AusleihManager::istMediumAusgeliehen(ausleihen, selectedMediumTitle)) {
        QMessageBox::warning(this, "Fehler", "Das Medium ist bereits ausgeliehen.");
        return;
    }

    // Für jede Person eine Ausleihe hinzufügen
    for (const auto& personName : selectedPersonNames) {
        AusleihManager::fuegeAusleiheHinzu(ausleihen, personName, selectedMediumTitle);
    }

    // Ausleihen speichern (hier die Reihenfolge korrigiert)
    AusleihManager::speichereAusleihenInDatei(ausleihen, "../ausleihen.txt");

    QMessageBox::information(this, "Erfolg", "Ausleihe erfolgreich hinzugefügt.\nPerson(en): " +
                             QString::fromStdString(selectedPersonNames.size() > 1 ? "mehrere" : selectedPersonNames[0]) +
                             "\nMedium: " + QString::fromStdString(selectedMediumTitle));

    accept();
}


std::vector<std::string> AusleihDialog::getSelectedPersonNames() const {
    return selectedPersonNames;
}

std::string AusleihDialog::getSelectedMediumTitle() const {
    return selectedMediumTitle;
}
