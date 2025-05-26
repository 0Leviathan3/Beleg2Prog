#include "medium.h"
#include <iostream>
using namespace std;
#include "CD.h"

CD::CD(string artist, string title, int duration)
    : Medium(title) // <--- Elternklasse richtig aufrufen!
{
    this->artist = artist;
    this->duration = duration;
}
CD::~CD() {

    // Destructor
}
void CD::displayInfo() const {
    cout << "CD Title: " << title << ", Artist: " << artist 
         << ", Duration: " << duration << " minutes" << endl;
}

string CD::getTitle() {
    return title;
}
string CD::getArtist() {
    return artist;
}
int CD::getDuration() const {
    return duration;
}
void CD::setTitle(const string& newTitle) {
    title = newTitle;
}
void CD::setArtist(const string& newArtist) {
    artist = newArtist;
}
void CD::setDuration(int newDuration) {
    duration = newDuration;
}