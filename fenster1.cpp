// fenster1.cpp
#include "fenster1.h"
#include <QLabel>
#include <QVBoxLayout>

Fenster1::Fenster1(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Fenster 1");
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Dies ist Fenster 1"));
}
