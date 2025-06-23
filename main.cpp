// main.cpp
#include <iostream>
#include <vector>
#include "medium.h"
#include "book.h"
#include "CD.h"
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

    // Create two objects of class Book
    book book1("The Hobbit", 234, "J.R.R. Tolkien");
    book book2("1984", 400, "George Orwell");

    // Create two objects of class CD
    //CD cd1("The Beatles", "Abbey Road", "Abbey Road");
    //CD cd2("Michael Jackson", "Thriller", "Thriller");


    std::vector<Person> personen = Datenbank::lesePersonenAusDatei("../beispiel.txt");
    BlueRay blueRay1("Inception","Goethe", 12);
    BlueRay blueRay2("The Matrix"," bla", 18);

    QApplication app(argc, argv);

    auto *window = new MainWindow(personen);

    window->show();
    return app.exec();

    

    return 0;
}