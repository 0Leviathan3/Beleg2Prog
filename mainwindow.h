/*Studeingruppe 24/041/63
Levin Grune
Matr Nr 56127 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>

class eingabe;
class ausgabetabelle;
class AusleihAnzeige;
class Person;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const std::vector<Person>& personen, QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
};

#endif // MAINWINDOW_H
