#include "medium.h"
#include <iostream>
using namespace std;

int Medium::nextId = 1;

Medium::Medium(string type, string titel)
    : title(titel), id(nextId++), type(type), ausgehlihen(false) {}

Medium::Medium(string type, string titel, int id)
    : title(titel), id(id), type(type), ausgehlihen(false) {}

void Medium::displayDetails() {
    cout << "Title: " << title << ", ID: " << id << ", type: " << type << endl;
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

bool Medium::getAusgeliehen() {
    return ausgehlihen;
}

void Medium::setTitle(const string& newTitle) {
    title = newTitle;
}

void Medium::settype(const string& newtype) {
    type = newtype;
}

void Medium::setId(int newId) {
    id = newId;
}

void Medium::setAusgeliehen(bool ausgeliehen) {
    ausgehlihen = ausgeliehen;
}

void Medium::setNextId(int id) {
    nextId = id;
}
