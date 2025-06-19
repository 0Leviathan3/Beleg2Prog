// fenster1.cpp
#include "fenster1.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>

Fenster1::Fenster1(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Fenster 1");
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Dies ist Fenster 1"));

    // Buttons
    neuhinzufügen = new QPushButton("Neues Element hinzufügen", this);
    layout->addWidget(neuhinzufügen);
    clearButton = new QPushButton("Felder leeren", this);
    layout->addWidget(clearButton);

    // Eingabefelder
    feld1 = new QLineEdit(this);
    feld2 = new QLineEdit(this);
    

    // Setze Platzhaltertexte für die Eingabefelder
    layout->addWidget(feld1);
    layout->addWidget(feld2);
    

    feld1->setPlaceholderText("Name");
    feld2->setPlaceholderText("Alter");

    connect(clearButton, &QPushButton::clicked, this, &Fenster1::leereFelder);
    connect(neuhinzufügen, &QPushButton::clicked, this, &Fenster1::sendePerson);


}
void Fenster1::leereFelder() {
    feld1->clear();
    feld2->clear();

}
void Fenster1::sendePerson() {
    QString name = feld1->text();
    int alter = feld2->text().toInt();  // Optional: Validierung einbauen

    if (!name.isEmpty()) {
        emit personHinzugefuegt(name, alter);
    }
}
