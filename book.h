#ifndef book_h
#define book_h

#include "medium.h"
#include <string>

class book : public Medium {

public:
    book(string artist, string title, int ISBN);
    ~book(); // Destructor
    void displayInfo() const;
    string getTitle();
    string getArtist();
    void setTitle(const string& newTitle);
    void setArtist(const string& newArtist);
    void setDuration(int newISBN);
    
    // Getter and Setter methods for title, artist, and duration
private:
    int ISBN;
    string artist;
};

#endif // book_h
