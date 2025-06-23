#include "eingabe.h"
#include "medium.h"
#include "book.h"
#include "BlueRay.h"
#include "datenbank.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QMessageBox>
#include <algorithm>
#include <QHeaderView>


eingabe::eingabe(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Medientabelle");

    auto *mainLayout = new QVBoxLayout(this);

    // Tabelle mit 4 Spalten: Checkbox, Titel, Typ, ID (z.B. ISBN/Fsk)
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "" << "Titel" << "Typ" << "ID");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLayout->addWidget(tableWidget);

    // Buttons erstellen
    btnSpeichern = new QPushButton("Speichern", this);
    btnLoeschen = new QPushButton("Ausgewählte löschen", this);
    btnHinzufuegen = new QPushButton("Neuhinzufügen", this);

    mainLayout->addWidget(btnSpeichern);
    mainLayout->addWidget(btnLoeschen);
    mainLayout->addWidget(btnHinzufuegen);

    setLayout(mainLayout);

    // Medien initial laden
    medien = Datenbank::leseMedienAusDatei("../mediumDb.txt");
    aktualisiereTabelle();

    connect(btnSpeichern, &QPushButton::clicked, this, &eingabe::speichereMedien);

    connect(btnLoeschen, &QPushButton::clicked, this, &eingabe::loescheAusgewaehlteZeilen);

    connect(btnHinzufuegen, &QPushButton::clicked, this, [this]() {
        // Beispiel: Demo-Medium hinzufügen
        fuegeMediumHinzu("Neues Medium", "Book", "0000");
    });
}

eingabe::~eingabe() {
    for (auto m : medien) {
        delete m;
    }
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

        // Titel, Typ, ID
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(medien[i]->getTitle())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(medien[i]->gettype())));

        QString idStr;
        if (medien[i]->gettype() == "Book") {
            auto buch = dynamic_cast<book*>(medien[i]);
            if (buch)
                idStr = QString::fromStdString(buch->getISBN());
        } else if (medien[i]->gettype() == "BlueRay") {
            auto br = dynamic_cast<BlueRay*>(medien[i]);
            if (br)
                idStr = QString::number(br->getFSK());
        } else {
            idStr = "n/a";
        }
        tableWidget->setItem(i, 3, new QTableWidgetItem(idStr));
    }
}

void eingabe::loescheAusgewaehlteZeilen() {
    std::vector<int> zeilenZuLoeschen;
    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        QWidget* widget = tableWidget->cellWidget(i, 0);
        if (widget) {
            QCheckBox* cb = widget->findChild<QCheckBox*>();
            if (cb && cb->isChecked())
                zeilenZuLoeschen.push_back(i);
        }
    }

    std::sort(zeilenZuLoeschen.rbegin(), zeilenZuLoeschen.rend());

    Datenbank::loescheMedien(medien, zeilenZuLoeschen);

    for (int idx : zeilenZuLoeschen)
        tableWidget->removeRow(idx);

    speichereMedien();
}

void eingabe::fuegeMediumHinzu(const QString& titel, const QString& typ, const QString& id) {
    Medium* neu = nullptr;

    if (typ == "Book") {
        neu = new book(titel.toStdString(), id.toStdString(), "Unbekannt");
    } else if (typ == "BlueRay") {
        neu = new BlueRay(titel.toStdString(), "Unbekannt", id.toInt());
    } else {
        QMessageBox::warning(this, "Fehler", "Unbekannter Medientyp!");
        return;
    }

    medien.push_back(neu);

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

    tableWidget->setItem(row, 1, new QTableWidgetItem(titel));
    tableWidget->setItem(row, 2, new QTableWidgetItem(typ));
    tableWidget->setItem(row, 3, new QTableWidgetItem(id));

    speichereMedien();
}

void eingabe::speichereMedien() {
    if (Datenbank::schreibeMedienInDatei(medien, "../mediumDb.txt")) {
        QMessageBox::information(this, "Erfolg", "Medien gespeichert.");
    } else {
        QMessageBox::warning(this, "Fehler", "Speichern fehlgeschlagen.");
    }
}
