#include "medium.h"
#include <iostream>
using namespace std;
#include "CD.h"


Medium::Medium(const string& title) : title(title) {}

CD::CD(string artist, string title, int duration)
    : Medium(title), artist(artist), duration(duration) {}
CD::~CD() {
    cout << "Destructor called for CD: " << title << endl;
}
void CD::displayInfo() const {
    cout << "CD: " << title << "\nArtist: " << artist << "\nDuration: " << duration << " minutes" << endl;
}