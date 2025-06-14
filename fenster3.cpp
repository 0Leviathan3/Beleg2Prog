// fenster3.cpp
#include "fenster3.h"
#include <QLabel>
#include <QVBoxLayout>

Fenster3::Fenster3(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Fenster 3");
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Dies ist Fenster 3"));
}
