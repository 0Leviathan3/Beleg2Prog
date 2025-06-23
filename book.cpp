#include "medium.h"
#include <iostream>
using namespace std;
#include "book.h"

book::book(string titel, int ISBN, string author) 
    : Medium( "Book",titel), ISBN(ISBN), author(author) {
    // Constructor implementation
}

void book::displayInfo() const {
    cout << "Author: " << author 
         << ", Title: " << title 
        << ", ISBN: " << ISBN
            << ", ID: " << id 
            << ", Type: " << type << endl;
}
int book::getISBN() const {
    return ISBN;
}
string book::getAuthor() const {
    return author;
}

void book::setISBN(int newISBN) {
    ISBN = newISBN;
}
void book::setAuthor(const string& newAuthor) {
    author = newAuthor;
}


    