#include "eingabe.h"

eingabe::eingabe(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Neues Fenster");

    auto *layout = new QVBoxLayout(this);
    auto *label = new QLabel("Dies ist ein neues Fenster (Widget)", this);
    layout->addWidget(label);

    setLayout(layout);
}

eingabe::~eingabe() {}
