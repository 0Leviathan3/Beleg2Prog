#include "ausleihanzeige.h"
#include "ausleihdialog.h"  
#include "ausleihmanager.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <fstream>
#include <sstream>
#include <QHeaderView>

AusleihAnzeige::AusleihAnzeige(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    ausleihTabelle = new QTableWidget(this);
    ausleihTabelle->setColumnCount(2);
    ausleihTabelle->setHorizontalHeaderLabels(QStringList() << "Person" << "Medium");
    ausleihTabelle->horizontalHeader()->setStretchLastSection(true);
    ausleihTabelle->setSelectionBehavior(QAbstractItemView::SelectRows);
    ausleihTabelle->setSelectionMode(QAbstractItemView::SingleSelection);
    ausleihTabelle->setEditTriggers(QAbstractItemView::NoEditTriggers);

    hinzufuegenButton = new QPushButton("Hinzufügen", this);
    loeschenButton = new QPushButton("Zurückgeben", this);

    layout->addWidget(ausleihTabelle);
    layout->addWidget(hinzufuegenButton);
    layout->addWidget(loeschenButton);

    connect(hinzufuegenButton, &QPushButton::clicked, this, &AusleihAnzeige::hinzufuegenGeklickt);
    connect(loeschenButton, &QPushButton::clicked, this, &AusleihAnzeige::loeschenGeklickt);

    ladeAusleihen();
}

void AusleihAnzeige::ladeAusleihen()
{
    personen.clear();
    medien.clear();

    std::ifstream file("../ausleihen.txt");
    if (!file.is_open()) {
        QMessageBox::warning(this, "Fehler", "Kann Datei ausleihen.txt nicht öffnen.");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string person, medium;

        
        if (std::getline(iss, person, ';') && std::getline(iss, medium)) {
            personen.push_back(person);
            medien.push_back(medium);
        }
    }

    file.close();

    aktualisiereTabelle();
}

void AusleihAnzeige::aktualisiereTabelle()
{
    ausleihTabelle->setRowCount(static_cast<int>(personen.size()));

    for (size_t i = 0; i < personen.size(); ++i) {
        ausleihTabelle->setItem(int(i), 0, new QTableWidgetItem(QString::fromStdString(personen[i])));
        ausleihTabelle->setItem(int(i), 1, new QTableWidgetItem(QString::fromStdString(medien[i])));
    }
}


void AusleihAnzeige::loeschenGeklickt()
{
    auto items = ausleihTabelle->selectedItems();
    if (items.isEmpty()) {
        QMessageBox::warning(this, "Löschen", "Bitte zuerst eine Ausleihe auswählen.");
        return;
    }

    int row = ausleihTabelle->row(items[0]);

    if (row < 0 || row >= static_cast<int>(personen.size()))
        return;

    // Datei neu schreiben ohne die gelöschte Zeile
    std::ifstream fileIn("../ausleihen.txt");
    if (!fileIn.is_open()) {
        QMessageBox::warning(this, "Fehler", "Kann Datei ausleihen.txt nicht öffnen.");
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    int currentLine = 0;
    while (std::getline(fileIn, line)) {
        if (currentLine != row) {
            lines.push_back(line);
        }
        currentLine++;
    }
    fileIn.close();

    std::ofstream fileOut("../ausleihen.txt", std::ios::trunc);
    if (!fileOut.is_open()) {
        QMessageBox::warning(this, "Fehler", "Kann Datei ausleihen.txt nicht schreiben.");
        return;
    }

    for (const auto& l : lines) {
        fileOut << l << "\n";
    }
    fileOut.close();

    ladeAusleihen();  // Tabelle neu laden
}
void AusleihAnzeige::hinzufuegenGeklickt() {
    AuswahlDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        // Ausleihe wurde im Dialog schon gespeichert
        ladeAusleihen();  // Tabelle aktualisieren
    }
}