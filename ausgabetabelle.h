#ifndef AUSGABETABELLE_H
#define AUSGABETABELLE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <vector>
#include "person.h"

class ausgabetabelle : public QWidget {
    Q_OBJECT

public:
    explicit ausgabetabelle(QWidget *parent = nullptr);
    void setPersonen(const std::vector<Person>& personen);
    ~ausgabetabelle();

    // sind funktionen die auf signale antowrten
private slots:
    void loescheAusgewaehlteZeilen();   // Slot für Button „Löschen“
    void oeffneNeuesFenster();          // Slot für Button „Neues Fenster“
    void fuegePersonHinzu(const QString &name, int alter);


private:
    QTableWidget *tableWidget;
    QPushButton *btnNeuesFenster;
    QPushButton *btnLoeschen;
    QPushButton *neuhinzufügen;
};

#endif // AUSGABETABELLE_H
