#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include "person.h"
#include "CD.h"
#include "BlueRay.h"
#include "book.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const std::vector<Person>& personen, QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
};

#endif // MAINWINDOW_H
