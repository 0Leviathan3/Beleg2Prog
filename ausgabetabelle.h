#ifndef AUSGABETABELLE_H
#define AUSGABETABELLE_H

#include <QWidget>
#include <QTableWidget>
#include <vector>
#include "person.h"

class ausgabetabelle : public QWidget {
    Q_OBJECT

public:
    explicit ausgabetabelle(QWidget *parent = nullptr);
    void setPersonen(const std::vector<Person>& personen);
    ~ausgabetabelle();

private:
    QTableWidget *tableWidget;
};

#endif // AUSGABETABELLE_H
