#include "medium.h"
#include <iostream>
using namespace std;
#include "BlueRay.h"

BlueRay::BlueRay(string titel,string director, int FSK)
    : Medium("BlueRay",titel), director(director), FSK(FSK) {
    // Constructor implementation
}
void BlueRay::displayInfo() const {
    cout << "Director: " << director 
         << ", Title: " << title 
         << " minutes, FSK: " << FSK 
         << ", ID: " << id 
         << ", Type: " << type << endl;
}
string BlueRay::getDirector() const {
    return director;
}
int BlueRay::getFSK() const {
    return FSK;
}
void BlueRay::setDirector(const string& newDirector) {
    director = newDirector;
}
void BlueRay::setFSK(int newFSK) {
    FSK = newFSK;
}
// Getter and Setter methods for title, artist, and duration