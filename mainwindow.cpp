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

MainWindow::MainWindow(const std::vector<Person>& personen, QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Stack-Widget für verschiedene Seiten
    auto *stackwidget = new QStackedWidget(this);
    auto *eingabeWidget = new eingabe();
    auto *ausgabeWidget = new ausgabetabelle();
    ausgabeWidget->setPersonen(personen);
    auto *ausleihAnzeigeWidget = new AusleihAnzeige();
    
    // Startseite mit Willkommen und Erklärungstext
    QWidget *startWidget = new QWidget();
    QVBoxLayout *startLayout = new QVBoxLayout(startWidget);

    QLabel *label = new QLabel("Willkommen zur Medienbibliothek!", startWidget);
    label->setAlignment(Qt::AlignCenter);
    startLayout->addWidget(label);

    // Erklärungstext zu den Buttons (Stichpunkte)
    QString erklaerung = 
        "• Hauptmenü: Zurück zur Startseite\n"
        "• Medien: Übersicht aller Medien\n"
        "• Personen: Übersicht der Personen\n"
        "• Ausleihen: Übersicht der Ausleihen";

    QLabel *erklaerungsLabel = new QLabel(erklaerung, startWidget);
    erklaerungsLabel->setAlignment(Qt::AlignLeft);
    erklaerungsLabel->setStyleSheet("font-size: 12pt; padding: 10px;"); // Optionales Styling
    startLayout->addWidget(erklaerungsLabel);

    // Widgets zum Stack hinzufügen
    stackwidget->addWidget(startWidget);           // Index 0
    stackwidget->addWidget(eingabeWidget);         // Index 1
    stackwidget->addWidget(ausgabeWidget);         // Index 2
    stackwidget->addWidget(ausleihAnzeigeWidget);  // Index 3

    layout->addWidget(stackwidget);

    // Buttons
    btn1 = new QPushButton("Hauptmenü", this);
    btn2 = new QPushButton("Anzeige", this);
    btn3 = new QPushButton("Personen", this);
    btn4 = new QPushButton("Ausleihen", this);

    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addWidget(btn4);

    // Button-Clicks mit Stack-Widget steuern (Capture stackwidget)
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
