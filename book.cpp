/*Studeingruppe 24/041/63
Levin Grune
Matr Nr 56127 */

#include "book.h"
#include <iostream>
using namespace std;

book::book(string titel, string ISBN, string author)
    : Medium("Book", titel), ISBN(ISBN), author(author) {}

book::book(string titel, string ISBN, string author, int id)
    : Medium("Book", titel, id), ISBN(ISBN), author(author) {}

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
