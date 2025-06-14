#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include "person.h"
#include "CD.h"
#include "BlueRay.h"
#include "book.h"
#include "fenster1.h"
#include "fenster2.h"
#include "fenster3.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addPerson(const Person& person);
    void addCD(const CD& cd);
    void addBlueRay(const BlueRay& blueRay);
    void addBook(const book& book);

private:
    QListWidget *personList;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;

    Fenster1 *win1;
    Fenster2 *win2;
    Fenster3 *win3;
    
};

#endif // MAINWINDOW_H