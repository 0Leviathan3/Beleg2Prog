#include "mainwindow.h"
#include "eingabe.h"
#include "person.h"
#include "ausgabetabelle.h"
#include "ausleihanzeige.h"
#include "ausleihmanager.h"
#include "datenbank.h"
#include "medium.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QDialogButtonBox>

MainWindow::MainWindow(const std::vector<Person>& personen, QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    auto *stackwidget = new QStackedWidget(this);
    auto *eingabeWidget = new eingabe();
    auto *ausgabeWidget = new ausgabetabelle();
    ausgabeWidget->setPersonen(personen);

    // ---------------------------
    // Ausleihen + Daten laden
    // ---------------------------
    auto *ausleihAnzeigeWidget = new AusleihAnzeige();

    // Übergabe der Zeiger, wie von setAusleihen erwartetWS

    // ---------------------------
    // Widgets hinzufügen
    // ---------------------------
    QWidget *startWidget = new QWidget();
    QVBoxLayout *startLayout = new QVBoxLayout(startWidget);
    QLabel *label = new QLabel("Willkommen zur Medienbibliothek!", startWidget);
    label->setAlignment(Qt::AlignCenter);
    startLayout->addWidget(label);

    stackwidget->addWidget(startWidget);           // Index 0
    stackwidget->addWidget(eingabeWidget);         // Index 1
    stackwidget->addWidget(ausgabeWidget);         // Index 2
    stackwidget->addWidget(ausleihAnzeigeWidget);  // Index 3

    layout->addWidget(stackwidget);

    btn1 = new QPushButton("Hauptmenü", this);
    btn2 = new QPushButton("Medien Anzeige", this);
    btn3 = new QPushButton("Personen", this);
    btn4 = new QPushButton("Ausleihen", this);

    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addWidget(btn4);

    // Verbindungen
    connect(btn1, &QPushButton::clicked, this, [stackwidget]() {
        stackwidget->setCurrentIndex(0);
    });
    connect(btn2, &QPushButton::clicked, this, [stackwidget]() {
        stackwidget->setCurrentIndex(1);
    });
    connect(btn3, &QPushButton::clicked, this, [stackwidget]() {
        stackwidget->setCurrentIndex(2);
    });
    connect(btn4, &QPushButton::clicked, this, [stackwidget]() {
        stackwidget->setCurrentIndex(3);
    });

    setCentralWidget(centralWidget);
    setWindowTitle("Main Window");
}

MainWindow::~MainWindow() {}
