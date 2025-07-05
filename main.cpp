// main.cpp
#include <iostream>
#include <vector>
#include "medium.h"
#include "book.h"
#include "BlueRay.h"
#include "person.h"
#include "datenbank.h"

#include "mainwindow.h"
#include <QApplication>
#include <QStackedWidget>
#include <QVBoxLayout>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Welcome to the Media Library!" << endl;


    std::vector<Person> personen = Datenbank::lesePersonenAusDatei("../beispiel.txt");
    std::vector<Medium*> medien;

    QApplication app(argc, argv);

    auto *window = new MainWindow(personen);

    window->show();
    return app.exec();

    

    return 0;
}