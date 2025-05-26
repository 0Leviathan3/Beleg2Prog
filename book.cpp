#include "medium.h"
#include <iostream>
using namespace std;
#include "book.h"

book::book(string artist, string title, int ISBN)
    : Medium(title) // <--- Elternklasse richtig aufrufen!
{
    this->artist = artist;
    this->ISBN = ISBN;
}
book::~book(){
    cout << "Destructor called for book: " << this->getTitle() << endl;
}
void book:: displayInfo() const{}
    string book::getTitle(){
        return title;
    }
    string book::getArtist(){
        return artist;
    }
    void book::setTitle(const string& newTitle){
        
    }
    void book::setArtist(const string& newArtist);
    void book::setDuration(int newISBN);