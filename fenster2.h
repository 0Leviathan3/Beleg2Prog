#ifndef FENSTER2_H
#define FENSTER2_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>

class Fenster2 : public QWidget
{
    Q_OBJECT

public:
    explicit Fenster2(QWidget *parent = nullptr);

private slots:
    void leereFelder();
    void sendePerson();
    void aktualisiereFelder(const QString &typ);

signals:
    void mediumHinzugefuegt(const QString &titel, const QString &person, const QString &id, const QString &typ, bool verfuegbar);

private:
    QPushButton *neuhinzufuegen;
    QPushButton *clearButton;
    QLineEdit *feld1; // Titel
    QLineEdit *feld3; // Autor/Regisseur
    QLineEdit *feld4; // ISBN/FSK
    QComboBox *comboBox;
    
};

#endif // FENSTER2_H
