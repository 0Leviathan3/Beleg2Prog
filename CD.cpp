#include "medium.h"
#include <iostream>
using namespace std;
#include "CD.h"

CD::CD(string artist, string title, int duration, string album):Medium(title, "CD"), 
    artist(artist), duration(duration), album(album) {
    }

void CD::displayInfo() const {
    cout << "Artist: " << artist 
         << ", Title: " << title 
         << ", Duration: " << duration 
         << " minutes, Album: " << album 
         << ", ID: " << id 
         << ", Type: " << type << endl;
}
int CD::getDuration() const {
    return duration;
}
string CD::getArtist() const {
    return artist;
}
string CD::getAlbum() const {
    return album;
}
void CD::setDuration(int newDuration) {
    duration = newDuration;
}
void CD::setArtist(const string& newArtist) {
    artist = newArtist;
}
void CD::setAlbum(const string& newAlbum) {
    album = newAlbum;
}