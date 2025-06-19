#include "ausgabetabelle.h"
#include "fenster1.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QCheckBox>
#include <QHBoxLayout>

ausgabetabelle::ausgabetabelle(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Ausgabetabelle");

    auto *mainLayout = new QVBoxLayout(this);

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3);  // 3 Spalten: Checkbox, Name, Alter
    tableWidget->setHorizontalHeaderLabels(QStringList() << "" << "Name" << "Alter");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLayout->addWidget(tableWidget);

    // Buttons
    QPushButton *btnNeuesFenster = new QPushButton("Neues Fenster öffnen", this);
    QPushButton *btnLoeschen = new QPushButton("Ausgewählte löschen", this);
    QPushButton *neuhinzufügen = new QPushButton("Neuhinzufügen", this);

    

    mainLayout->addWidget(btnNeuesFenster);
    mainLayout->addWidget(btnLoeschen);
    mainLayout->addWidget(neuhinzufügen);

    setLayout(mainLayout);

    // Noch keine Funktionen – nur Platzhalter
    connect(btnNeuesFenster, &QPushButton::clicked, this, []() {
        // Fenster öffnen Logik
    });

    connect(btnLoeschen, &QPushButton::clicked, this, []() {
        // Löschen-Logik
    });
    connect(neuhinzufügen, &QPushButton::clicked, this, [this]() {
        // Neues Fenster erstellen
        Fenster1 *neuesFenster = new Fenster1();
        connect(neuesFenster, &Fenster1::personHinzugefuegt, this, &ausgabetabelle::fuegePersonHinzu);
        neuesFenster->show();
    });
}

void ausgabetabelle::setPersonen(const std::vector<Person>& personen)
{
    tableWidget->setRowCount(static_cast<int>(personen.size()));

    for (int i = 0; i < personen.size(); ++i) {
        // Checkbox in eigene Spalte (als Widget)
        QWidget *checkBoxWidget = new QWidget();
        QCheckBox *checkBox = new QCheckBox();
        QHBoxLayout *layoutCheck = new QHBoxLayout(checkBoxWidget);
        layoutCheck->addWidget(checkBox);
        layoutCheck->setAlignment(Qt::AlignCenter);
        layoutCheck->setContentsMargins(0, 0, 0, 0);
        checkBoxWidget->setLayout(layoutCheck);
        tableWidget->setCellWidget(i, 0, checkBoxWidget);

        // Name
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(personen[i].getName())));
        // Alter
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(personen[i].getAge())));
    }
}

ausgabetabelle::~ausgabetabelle() {}
void ausgabetabelle::loescheAusgewaehlteZeilen() {
    // Rückwärts durchlaufen, da sich die Indizes beim Löschen verschieben
    for (int i = tableWidget->rowCount() - 1; i >= 0; --i) {
        QWidget *widget = tableWidget->cellWidget(i, 0);
        if (!widget) continue;

        QCheckBox *checkBox = widget->findChild<QCheckBox *>();
        if (checkBox && checkBox->isChecked()) {
            tableWidget->removeRow(i);
        }
    }
}

void ausgabetabelle::oeffneNeuesFenster() {
    // Platzhalter für neues Fenster
    QWidget *fenster = new QWidget();
    fenster->setWindowTitle("Neues Fenster");
    fenster->resize(300, 200);
    fenster->show();
}
void ausgabetabelle::fuegePersonHinzu(const QString &name, int alter) {
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

    tableWidget->setItem(row, 1, new QTableWidgetItem(name));
    tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(alter)));
}
