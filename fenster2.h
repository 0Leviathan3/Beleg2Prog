#ifndef FENSTER2_H
#define FENSTER2_H

#include <QWidget>
#include <QPushButton>

class eingabefenster;  // Vorwärtsdeklaration

class Fenster2 : public QWidget {
    Q_OBJECT

public:
    Fenster2(QWidget *parent = nullptr);

private slots:
    void openeingabefenster();

private:
    QPushButton *openButton;
    eingabefenster *eingabeFensterPtr = nullptr;  // anderer Name
};

#endif // FENSTER2_H
