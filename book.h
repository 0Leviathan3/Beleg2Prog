#ifndef BOOK_H
#define BOOK_H

#include "medium.h"

class Book : public Medium {
public:
    Book(const string& title, const string& author, int pages);
    void displayDetails() const override;
    ~Book(); // Destructor

private:
    string author;
    int pages;

    
};
#endif // BOOK_H