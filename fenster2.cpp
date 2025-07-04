#include "fenster2.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

Fenster2::Fenster2(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Medium hinzufügen");
    resize(300, 200);

    feld1 = new QLineEdit(this); // Titel
    feld3 = new QLineEdit(this); // Autor/Regisseur
    feld4 = new QLineEdit(this); // ISBN/FSK

    comboBox = new QComboBox(this);
    comboBox->addItem("Book");
    comboBox->addItem("BlueRay");

    neuhinzufuegen = new QPushButton("Hinzufügen", this);
    clearButton = new QPushButton("Leeren", this);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(comboBox);
    layout->addWidget(feld1);
    layout->addWidget(feld3);
    layout->addWidget(feld4);

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(neuhinzufuegen);
    buttonLayout->addWidget(clearButton);
    layout->addLayout(buttonLayout);

    connect(neuhinzufuegen, &QPushButton::clicked, this, &Fenster2::sendePerson);
    connect(clearButton, &QPushButton::clicked, this, &Fenster2::leereFelder);
    connect(comboBox, &QComboBox::currentTextChanged, this, &Fenster2::aktualisiereFelder);

    // Initiale Platzhalter setzen
    aktualisiereFelder(comboBox->currentText());
}

void Fenster2::leereFelder()
{
    feld1->clear();
    feld3->clear();
    feld4->clear();
}

void Fenster2::aktualisiereFelder(const QString &typ)
{
    if (typ == "Book") {
        feld1->setPlaceholderText("Titel");
        feld3->setPlaceholderText("Autor");
        feld4->setPlaceholderText("ISBN");
    } else if (typ == "BlueRay") {
        feld1->setPlaceholderText("Titel");
        feld3->setPlaceholderText("Regisseur");
        feld4->setPlaceholderText("FSK");
    }
}

void Fenster2::sendePerson()
{
    QString titel = feld1->text();
    QString person = feld3->text();
    QString id = feld4->text();
    QString typ = comboBox->currentText();
    bool verfuegbar = false; 

    if (titel.isEmpty() || person.isEmpty() || id.isEmpty()) {
        QMessageBox::warning(this, "Fehler", "Bitte alle Felder ausfüllen!");
        return;
    }

    // Prüfe, ob id nur aus Zahlen besteht (für ISBN oder FSK)
    bool ok;
    int nummer = id.toInt(&ok);
    if (!ok) {
        QString feldName = (typ == "Book") ? "ISBN" : "FSK";
        QMessageBox::warning(this, "Fehler", QString("Bitte nur Zahlen für %1 eingeben.").arg(feldName));
        return;
    }

    emit mediumHinzugefuegt(titel, person, id, typ, verfuegbar);
    close();
}
