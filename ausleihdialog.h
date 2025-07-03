#ifndef AUSWAHLDIALOG_H
#define AUSWAHLDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QStackedWidget>
#include "datenbank.h"
#include "medium.h"
#include "person.h"

class AuswahlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuswahlDialog(QWidget *parent = nullptr);

    Medium* getAusgewaehltesMedium() const;
    Person getAusgewaehltePerson() const;

private slots:
    void weiter();       // Wechsel von Medien zu Personen
    void bestaetigen();  // Auswahl bestätigen

private:
    QStackedWidget* stackedWidget;

    QTableWidget* medienTabelle;
    QTableWidget* personenTabelle;

    QPushButton* weiterButton;
    QPushButton* bestaetigenButton;

    std::vector<Medium*> medien;
    std::vector<Person> personen;

    Medium* ausgewaehltesMedium = nullptr;
    Person ausgewaehltePerson;
};

#endif // AUSWAHLDIALOG_H
