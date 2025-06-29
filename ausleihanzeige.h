#ifndef AUSLEIHANZEIGE_H
#define AUSLEIHANZEIGE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
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
                      const std::vector<Medium> &medien);

    std::vector<int> getAusgewaehlteZeilen() const;

signals:
    void hinzufuegenClicked();
    void loeschenClicked();

private:
    QTableWidget *tableWidget;
    QPushButton *addButton;
    QPushButton *deleteButton;
};

#endif // AUSLEIHANZEIGE_H
