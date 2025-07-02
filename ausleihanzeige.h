#ifndef AUSLEIHANZEIGE_H
#define AUSLEIHANZEIGE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <vector>
#include "ausleihmanager.h"
#include "person.h"
#include "medium.h"

class AusleihAnzeige : public QWidget
{
    Q_OBJECT

public:
    explicit AusleihAnzeige(QWidget *parent = nullptr);

    void setAusleihen(const std::vector<Ausleihe> &ausleihen,
                      const std::vector<Person> &personen,
                      const std::vector<Medium*> &medien);

    std::vector<int> getAusgewaehlteZeilen() const;

signals:
    void hinzufuegenClicked();

private:
    QTableWidget *tableWidget;
    QPushButton *addButton;
    QPushButton *deleteButton;

    std::vector<Person> personen;
    std::vector<Medium*> medien;
    std::vector<Ausleihe> aktuelleAusleihen;
};

#endif // AUSLEIHANZEIGE_H
