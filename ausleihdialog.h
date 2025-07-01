#ifndef AUSLEIHDIALOG_H
#define AUSLEIHDIALOG_H

#include <QDialog>
#include <QComboBox>
#include "medium.h"
#include "person.h"

class AusleihDialog : public QDialog {
    Q_OBJECT

public:
    AusleihDialog(const std::vector<Medium*>& medien,
                  const std::vector<Person>& personen,
                  QWidget *parent = nullptr);

    int getSelectedMediumId() const;
    int getSelectedPersonId() const;

private:
    QComboBox *mediumBox;
    QComboBox *personBox;
    std::vector<Medium*> verfuegbareMedien;
    std::vector<Person> allePersonen;
};

#endif // AUSLEIHDIALOG_H
