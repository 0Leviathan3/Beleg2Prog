#ifndef BOOK_H
#define BOOK_H

#include "medium.h"
#include <string>

class book : public Medium {
public:
    book(string titel, string ISBN, string author);
    book(string titel, string ISBN, string author, int id); 

    void displayInfo() const;
    string getISBN() const;
    string getAuthor() const;
    void setISBN(const string& newISBN);
    void setAuthor(const string& newAuthor);

private:
    string ISBN;
    string author;
};

#endif // BOOK_H
