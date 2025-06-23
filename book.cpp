#include "medium.h"
#include <iostream>
using namespace std;
#include "book.h"

book::book(string titel, string ISBN, string author) 
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

string book::getAuthor() const {
    return author;
}

string book::getISBN() const {
    return ISBN;
}
void book::setAuthor(const string& newAuthor) {
    author = newAuthor;
}
void book::setISBN(const string& newISBN) {
    ISBN = newISBN;
}


    