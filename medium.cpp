#include <iostream>
using namespace std;
#include "medium.h"

int Medium::nextId = 1; // Static member to keep track of the next ID

Medium::Medium(string titel, string genre) 
    : title(titel), id(nextId++), genre(genre) {
    // Constructor implementation
}
Medium::~Medium() {
    // Destructor implementation
}
void Medium::displayDetails() {
    cout << "Title: " << title  
         << ", ID: " << id << ", Genre: " << genre << endl;
}
string Medium::getTitle() const {
    return title;
}


int Medium::getId() const {
    return id;
}
string Medium::getGenre() const {
    return genre;
}
void Medium::setTitle(const string& newTitle) {
    title = newTitle;
}

void Medium::setId(int newId) {
    id = newId;
}
void Medium::setGenre(const string& newGenre) {
    genre = newGenre;
}


