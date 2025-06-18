#include "ausgabetabelle.h"
#include <QVBoxLayout>


ausgabetabelle::ausgabetabelle(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Ausgabetabelle");

    auto *layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(2);  // 2 Spalten: Name und Alter
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Alter");
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  // Nicht editierbar

    layout->addWidget(tableWidget);
    setLayout(layout);
}

void ausgabetabelle::setPersonen(const std::vector<Person>& personen)
{
    tableWidget->setRowCount(static_cast<int>(personen.size()));  // Zeilenanzahl = Personenanzahl

    for (int i = 0; i < personen.size(); ++i) {
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(personen[i].getName())));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(personen[i].getAge())));
    }
}

ausgabetabelle::~ausgabetabelle() {}
