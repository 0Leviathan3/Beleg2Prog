#ifndef book_h
#define book_h

#include "medium.h"
#include <string>

class book : public Medium {

public:
    book(string titel,string ISBN, string author);
    void displayInfo() const;
    string getISBN() const;
    string getAuthor() const;
    void setISBN(const string& newISBN);
    void setAuthor(const string& newAuthor);
    
    // Getter and Setter methods for title, artist, and duration
private:
    string ISBN;// muss ein string werden da auch null vorne stehen kann 
    string author; // Number of pages in the book
};

#endif // book_h
