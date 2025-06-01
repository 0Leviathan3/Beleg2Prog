#include "medium.h"
#include <iostream>
using namespace std;
#include "book.h"

book::book(string titel, int ISBN, string author, int pages) 
    : Medium(titel, "Book"), ISBN(ISBN), author(author), pages(pages) {
    // Constructor implementation
}
book::~book() {
    // Destructor implementation
}
void book::displayInfo() const {
    cout << "Author: " << author 
         << ", Title: " << title 
         << ", Pages: " << pages 
        << ", ISBN: " << ISBN
            << ", ID: " << id 
            << ", Genre: " << genre << endl;
}
int book::getISBN() const {
    return ISBN;
}
string book::getAuthor() const {
    return author;
}
int book::getPages() const {
    return pages;
}
void book::setISBN(int newISBN) {
    ISBN = newISBN;
}
void book::setAuthor(const string& newAuthor) {
    author = newAuthor;
}
void book::setPages(int newPages) {
    pages = newPages;
}

    