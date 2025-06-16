#ifndef EINGABE_H
#define EINGABE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class eingabe : public QWidget {
    Q_OBJECT

public:
    explicit eingabe(QWidget *parent = nullptr);
    ~eingabe();
};

#endif // EINGABE_H
