#ifndef AUSLEIHDIALOG_H
#define AUSLEIHDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <vector>
#include <string>
#include "person.h"
#include "medium.h"

class AusleihDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AusleihDialog(QWidget *parent = nullptr);

    std::vector<std::string> getSelectedPersonNames() const;
    std::string getSelectedMediumTitle() const;

private slots:
    void geheZuMedienAuswahl();
    void ausleihen();

private:
    void erzeugePersonenTabelle();
    void erzeugeMedienAuswahl();

    std::vector<Person> allePersonen;
    std::vector<Medium*> alleMedien;
    std::vector<Medium*> verfuegbareMedien;

    std::vector<std::string> selectedPersonNames;
    std::string selectedMediumTitle;

    QStackedWidget *stack = nullptr;

    // Personen Auswahl
    QTableWidget *personenTabelle = nullptr;
    QPushButton *weiterButton = nullptr;

    // Medien Auswahl
    QTableWidget *medienTabelle = nullptr;
    QPushButton *ausleihenButton = nullptr;
};

#endif // AUSLEIHDIALOG_H
