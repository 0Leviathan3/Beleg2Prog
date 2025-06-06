// main.cpp
#include <iostream>
#include "medium.h"
#include "book.h"
#include "CD.h"
#include "BlueRay.h"
#include "person.h"

#include "mainwindow.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Welcome to the Media Library!" << endl;

    // Create two objects of class Book
    book book1("The Hobbit",8765, "J.R.R. Tolkien", 234);
    book book2("1984",3456, "George Orwell", 400);

    // Create two objects of class CD
    CD cd1("The Beatles", "Abbey Road", 47, "Abbey Road");
    CD cd2("Michael Jackson", "Thriller", 42, "Thriller");

    // Output the initial state of the objects
  /*  cout << "\nInitial state:" << endl;
    book1.displayInfo();
    book2.displayInfo();
    cd1.displayInfo();
    cd2.displayInfo();

    // Modify the objects
    book1.setTitle("The Lord of the Rings");
    book1.setPages(400);
    book2.setTitle("Animal Farm");
    book2.setPages(8765);

    cd1.setTitle("Let It Be");
    cd1.setDuration(700);
    cd2.setTitle("Bad");
    cd2.setDuration(1950087);

    // Output the modified state of the objects
    cout << "\nModified state:" << endl;
    book1.displayInfo();
    book2.displayInfo();
    cd1.displayInfo();
    cd2.displayInfo();
*/

Person p1("John", 30);
    Person p2("Jane", 25);

    QApplication app(argc, argv);

    MainWindow window;
    
    window.addPerson(p1);
    window.addPerson(p2);

    window.show();
    return app.exec();

    

    return 0;
}