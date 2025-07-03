#ifndef AUSLEIHDIALOG_H
#define AUSLEIHDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QStackedWidget>
#include <vector>
#include <string>
#include "person.h"
#include "medium.h"

class AusleihDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AusleihDialog(const std::vector<Person*>& personen,
                           const std::vector<Medium*>& medien,
                           QWidget *parent = nullptr);

    std::vector<std::string> getAusgewaehltePersonen() const;
    std::string getAusgewaehltesMedium() const;

private slots:
    void bestaetigen();

private:
    QStackedWidget *stackedWidget;
    QTableWidget *personenTabelle;
    QTableWidget *medienTabelle;

    std::vector<std::string> selectedPersonNamen;
    std::string selectedMediumTitel;
};

#endif // AUSLEIHDIALOG_H
