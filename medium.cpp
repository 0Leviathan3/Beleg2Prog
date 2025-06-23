#include <iostream>
#include <string>
using namespace std;
#include "medium.h"

int Medium::nextId = 1; // Static member to keep track of the next ID

Medium::Medium(string type,string titel) 
    : title(titel), id(nextId++), type(type) {
    // Constructor implementation
}

void Medium::displayDetails() {
    cout << "Title: " << title  
         << ", ID: " << id << ", type: " << type << endl;
}
string Medium::getTitle() const {
    return title;
}


int Medium::getId() const {
    return id;
}
string Medium::gettype() const {
    return type;
}
void Medium::setTitle(const string& newTitle) {
    title = newTitle;
}

void Medium::setId(int newId) {
    id = newId;
}
void Medium::settype(const string& newtype) {
    type = newtype;
}
bool Medium::getAusgeliehen() {
    return ausgehlihen;
}
void Medium::setAusgeliehen(bool ausgeliehen) {
    ausgehlihen = ausgeliehen;
}

