#include "mainwindow.h"
#include "eingabe.h"
#include "person.h"
#include "ausgabetabelle.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

#include <vector>


MainWindow::MainWindow(const std::vector<Person>& personen, QWidget *parent)
    : QMainWindow(parent){

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    auto *stackwidget = new QStackedWidget(this);
    auto *eingabeWidget = new eingabe();  // Dein benutzerdefiniertes Widget
    auto *ausgabeWidget = new ausgabetabelle(); // Dein benutzerdefiniertes Widget
    ausgabeWidget->setPersonen(personen);

    QWidget *startWidget = new QWidget();
    QVBoxLayout *startLayout = new QVBoxLayout(startWidget);
    QLabel *label = new QLabel("Willkommen zur Medienbibliothek!", startWidget);
    label->setAlignment(Qt::AlignCenter);
    startLayout->addWidget(label);
    stackwidget->addWidget(startWidget);
    stackwidget->addWidget(eingabeWidget); // Index 1
    stackwidget->addWidget(ausgabeWidget); // Index 2

    layout->addWidget(stackwidget);
    //layout->addWidget(personList);


    btn1 = new QPushButton("Fenster 1 öffnen", this);
    btn2 = new QPushButton("Medien Anzeige", this);
    btn3 = new QPushButton("Ausleihen", this);
    btn4 = new QPushButton("Personen Anzeige", this);

    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addWidget(btn4);

    connect(btn1, &QPushButton::clicked, this, [stackwidget]() {
        stackwidget->setCurrentIndex(0);  // Zeige das Eingabe-Widget
    });
    connect(btn2, &QPushButton::clicked, this, [stackwidget]() {
        stackwidget->setCurrentIndex(1);  // Zeige das Dummy-Widget
    });
    connect(btn3, &QPushButton::clicked, this, [stackwidget]() {
        stackwidget->setCurrentIndex(2);  // Zeige das Ausgabe-Widget
    });


    setCentralWidget(centralWidget);
    setWindowTitle("Main Window");
}



MainWindow::~MainWindow() {}

