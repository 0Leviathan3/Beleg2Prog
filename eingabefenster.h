#ifndef EINGABEFENSTER_H
#define EINGABEFENSTER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class eingabefenster : public QWidget {
    Q_OBJECT

public:
    explicit eingabefenster(QWidget *parent = nullptr);

private slots:
    void onOkClicked();
    void onClearClicked();
    void onCloseClicked();  

private:
    QLineEdit *feld1;
    QLineEdit *feld2;
    QLineEdit *feld3;
    QLineEdit *feld4;
    QPushButton *okButton;
    QPushButton *clearButton;
    QPushButton *closeButton;  // Neuer Button
};

#endif // EINGABEFENSTER_H
