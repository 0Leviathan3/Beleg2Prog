#include "fenster2.h"
#include "eingabefenster.h"
#include <QVBoxLayout>
#include <QLabel>

Fenster2::Fenster2(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Fenster 2");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Dies ist Fenster 2"));

    openButton = new QPushButton("Dateneingabe öffnen", this);
    layout->addWidget(openButton);

    connect(openButton, &QPushButton::clicked, this, &Fenster2::openeingabefenster);
}

void Fenster2::openeingabefenster()
{
    if (eingabeFensterPtr) {
        eingabeFensterPtr->deleteLater();
        eingabeFensterPtr = nullptr;
    }

    eingabeFensterPtr = new eingabefenster(this);
    eingabeFensterPtr->show();
    eingabeFensterPtr->raise();
    eingabeFensterPtr->activateWindow();
}
