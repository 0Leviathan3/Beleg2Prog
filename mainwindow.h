#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include "person.h"
#include "CD.h"
#include "BlueRay.h"
#include "book.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    

private:
    QListWidget *personList;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    
};

#endif // MAINWINDOW_H