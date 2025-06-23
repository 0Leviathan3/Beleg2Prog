#ifndef EINGABE_H
#define EINGABE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <vector>
#include "medium.h"

class eingabe : public QWidget {
    Q_OBJECT

public:
    explicit eingabe(QWidget *parent = nullptr);
    ~eingabe();

    void setMedien(const std::vector<Medium*>& medien);

private slots:
    void loescheAusgewaehlteZeilen();
    void fuegeMediumHinzu(const QString& titel, const QString& typ, const QString& id);
    void speichereMedien();

private:
    void aktualisiereTabelle();

    QTableWidget* tableWidget;
    QPushButton* btnSpeichern;
    QPushButton* btnLoeschen;
    QPushButton* btnHinzufuegen;

    std::vector<Medium*> medien;
};

#endif // EINGABE_H
