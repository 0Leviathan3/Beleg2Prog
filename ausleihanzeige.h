/*Studeingruppe 24/041/63
Levin Grune
Matr Nr 56127 */

#ifndef AUSLEIHANZEIGE_H
#define AUSLEIHANZEIGE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <vector>
#include <string>

class AusleihAnzeige : public QWidget
{
    Q_OBJECT
public:
    explicit AusleihAnzeige(QWidget *parent = nullptr);

private slots:
    void hinzufuegenGeklickt();
    void loeschenGeklickt();

private:
    void ladeAusleihen(); // Lädt ausleihen.txt in die Tabelle
    void aktualisiereTabelle();

    QTableWidget *ausleihTabelle;
    QPushButton *hinzufuegenButton;
    QPushButton *loeschenButton;

    // Zwei Vektoren für Person und Medium
    std::vector<std::string> personen;
    std::vector<std::string> medien;
};

#endif // AUSLEIHANZEIGE_H
