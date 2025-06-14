#include "eingabefenster.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>

eingabefenster::eingabefenster(QWidget *parent)
    : QWidget(parent) {
    setAttribute(Qt::WA_DeleteOnClose);

    feld1 = new QLineEdit(this);
    feld2 = new QLineEdit(this);
    feld3 = new QLineEdit(this);
    feld4 = new QLineEdit(this);

    okButton = new QPushButton("OK", this);
    clearButton = new QPushButton("Löschen", this);
    closeButton = new QPushButton("Schließen", this); // Neuer Button

    setFixedSize(300, 200);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Feld 1:", feld1);
    formLayout->addRow("Feld 2:", feld2);
    formLayout->addRow("Feld 3:", feld3);
    formLayout->addRow("Feld 4:", feld4);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("Dateneingabe");

    // Button-Verbindungen
    connect(okButton, &QPushButton::clicked, this, &eingabefenster::onOkClicked);
    connect(clearButton, &QPushButton::clicked, this, &eingabefenster::onClearClicked);
    connect(closeButton, &QPushButton::clicked, this, &eingabefenster::onCloseClicked);
}

void eingabefenster::onOkClicked() {
    QString daten = QString("Feld 1: %1\nFeld 2: %2\nFeld 3: %3\nFeld 4: %4")
                        .arg(feld1->text())
                        .arg(feld2->text())
                        .arg(feld3->text())
                        .arg(feld4->text());

    QMessageBox::information(this, "Eingaben", daten);
}

void eingabefenster::onClearClicked() {
    feld1->clear();
    feld2->clear();
    feld3->clear();
    feld4->clear();
}

void eingabefenster::onCloseClicked() {
    this->close(); // Fenster schließen
}
