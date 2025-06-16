#include "mainwindow.h"
#include "eingabe.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), personList(new QListWidget(this)) {

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    auto *stackwidget = new QStackedWidget(this);
    auto *eingabeWidget = new eingabe();  // Dein benutzerdefiniertes Widget

    // Ein Platzhalter für "Fenster 0"
    QWidget *dummy = new QWidget();
    stackwidget->addWidget(dummy);        // Index 0
    stackwidget->addWidget(eingabeWidget); // Index 1

    layout->addWidget(stackwidget);
    layout->addWidget(personList);

    btn1 = new QPushButton("Fenster 1 öffnen", this);
    btn2 = new QPushButton("Fenster 2 öffnen", this);
    btn3 = new QPushButton("Fenster 3 öffnen", this);

    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);

    connect(btn1, &QPushButton::clicked, this, [stackwidget]() {
        stackwidget->setCurrentIndex(1);  // Zeige das Eingabe-Widget
    });
    connect(btn2, &QPushButton::clicked, this, [stackwidget]() {
        stackwidget->setCurrentIndex(0);  // Zeige das Dummy-Widget
    });


    setCentralWidget(centralWidget);
    setWindowTitle("Main Window");
}



MainWindow::~MainWindow() {}

