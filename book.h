#ifndef book_h
#define book_h

#include "medium.h"
#include <string>

class book : public Medium {

public:
    book(string titel,int ISBN, string author);
    void displayInfo() const;
    int getISBN() const;
    string getAuthor() const;
    void setISBN(int newISBN);
    void setAuthor(const string& newAuthor);
    
    // Getter and Setter methods for title, artist, and duration
private:
    int ISBN;// muss ein string werden da auch null vorne stehen kann 
    string author; // Number of pages in the book
};

#endif // book_h
