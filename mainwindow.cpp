#include "mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), personList(new QListWidget(this)) {
    // Set up the layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(personList);
    setCentralWidget(centralWidget);

    setWindowTitle("Person List");

    btn1 = new QPushButton("Fenster 1 öffnen", this);
btn2 = new QPushButton("Fenster 2 öffnen", this);
btn3 = new QPushButton("Fenster 3 öffnen", this);

btn1->setGeometry(10, 10, 150, 30);
btn2->setGeometry(10, 50, 150, 30);
btn3->setGeometry(10, 90, 150, 30);

// Fenster-Objekte erzeugen
win1 = new Fenster1();
win2 = new Fenster2();
win3 = new Fenster3();

// Signale verbinden
connect(btn1, &QPushButton::clicked, win1, &QWidget::show);
connect(btn2, &QPushButton::clicked, win2, &QWidget::show);
connect(btn3, &QPushButton::clicked, win3, &QWidget::show);
}

MainWindow::~MainWindow() {}

void MainWindow::addPerson(const Person& person) {
    QString personInfo = QString("Name: %1, Age: %2")
                             .arg(QString::fromStdString(person.getName()))
                             .arg(person.getAge());
    personList->addItem(personInfo);
}

void MainWindow::addCD(const CD& cd) {
    QString cdInfo = QString("CD - Artist: %1, Album: %2, Title: %3, Duration: %4 min")
                         .arg(QString::fromStdString(cd.getArtist()))
                         .arg(QString::fromStdString(cd.getAlbum()))
                         .arg(QString::fromStdString(cd.getTitle()))
                         .arg(cd.getDuration());

    personList->addItem(cdInfo); // oder besser: listWidget
}
void MainWindow::addBlueRay(const BlueRay& blueRay) {
    QString blueRayInfo = QString("BlueRay - Title: %1, Director: %2, Duration: %3 min, FSK: %4")
                              .arg(QString::fromStdString(blueRay.getTitle()))
                              .arg(QString::fromStdString(blueRay.getDirector()))
                              .arg(blueRay.getDuration())
                              .arg(blueRay.getFSK());

    personList->addItem(blueRayInfo);
}
void MainWindow::addBook(const book& book) {
    QString bookInfo = QString("Book - Title: %1, Author: %2, Pages: %3")
                           .arg(QString::fromStdString(book.getTitle()))
                           .arg(QString::fromStdString(book.getAuthor()))
                           .arg(book.getPages());

    personList->addItem(bookInfo);
}

