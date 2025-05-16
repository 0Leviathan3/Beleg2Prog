#include "book.h"
#include <iostream>
using namespace std;

Book::Book(const string& title, const string& author, int pages)
    : Medium(title), author(author), pages(pages) {}

void Book::displayDetails() const {
    cout << "Book: " << title << "\nAuthor: " << author << "\nPages: " << pages << endl;
}
Book::~Book() {
    cout << "Destructor called for Book: " << title << endl;
}