// fenster1.h
#ifndef FENSTER1_H
#define FENSTER1_H

#include <QTableWidget>
#include <QPushButton>

#include <QWidget>

class Fenster1 : public QWidget
{
    Q_OBJECT

public:
    Fenster1(QWidget *parent = nullptr);
private slots:
    void leereFelder();
    void sendePerson();
signals:
    void personHinzugefuegt(const QString &name, int alter);
private:
    QPushButton *neuhinzufügen;
    QPushButton *clearButton;
    QLineEdit *feld1;
    QLineEdit *feld2;
    
};

#endif // FENSTER1_H