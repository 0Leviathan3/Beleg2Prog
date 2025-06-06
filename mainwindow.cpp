#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), personList(new QListWidget(this)) {
    // Set up the layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(personList);
    setCentralWidget(centralWidget);

    setWindowTitle("Person List");
}

MainWindow::~MainWindow() {}

void MainWindow::addPerson(const Person& person) {
    QString personInfo = QString("Name: %1, Age: %2")
                             .arg(QString::fromStdString(person.getName()))
                             .arg(person.getAge());
    personList->addItem(personInfo);
}