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

private slots:
    void loescheAusgewaehlteZeilen();
    void oeffneNeuesFenster();
    void fuegePersonHinzu(const QString &name, int alter);

private:
    void aktualisiereTabelle();

    QTableWidget *tableWidget;
    QPushButton *btnSpeichern;
    QPushButton *btnLoeschen;
    QPushButton *neuhinzufügen;

    std::vector<Person> personen;
};

#endif // AUSGABETABELLE_H
