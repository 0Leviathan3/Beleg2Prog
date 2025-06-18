// main.cpp
#include <iostream>
#include <vector>
#include "medium.h"
#include "book.h"
#include "CD.h"
#include "BlueRay.h"
#include "person.h"

#include "mainwindow.h"
#include <QApplication>
#include <QStackedWidget>
#include <QVBoxLayout>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Welcome to the Media Library!" << endl;

    // Create two objects of class Book
    book book1("The Hobbit",8765, "J.R.R. Tolkien", 234);
    book book2("1984",3456, "George Orwell", 400);

    // Create two objects of class CD
    CD cd1("The Beatles", "Abbey Road", 47, "Abbey Road");
    CD cd2("Michael Jackson", "Thriller", 42, "Thriller");


    Person p1("John", 30);
    Person p2("Jane", 25);

    std::vector<Person> personen = {
        p1,
        p2
     };
    BlueRay blueRay1("Inception","Goethe", 148, 12);
    BlueRay blueRay2("The Matrix"," bla", 136, 18);

    QApplication app(argc, argv);

    auto *window = new MainWindow(personen);

    window->show();
    return app.exec();

    

    return 0;
}