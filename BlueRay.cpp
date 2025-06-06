#include "medium.h"
#include <iostream>
using namespace std;
#include "BlueRay.h"

BlueRay::BlueRay(string director, string title, int duration, int FSK)
    : Medium(title, "BlueRay"), director(director), duration(duration), FSK(FSK) {
    // Constructor implementation
}
void BlueRay::displayInfo() const {
    cout << "Director: " << director 
         << ", Title: " << title 
         << ", Duration: " << duration 
         << " minutes, FSK: " << FSK 
         << ", ID: " << id 
         << ", Type: " << type << endl;
}
int BlueRay::getDuration() const {
    return duration;
}
string BlueRay::getDirector() const {
    return director;
}
int BlueRay::getFSK() const {
    return FSK;
}
void BlueRay::setDuration(int newDuration) {
    duration = newDuration;
}
void BlueRay::setDirector(const string& newDirector) {
    director = newDirector;
}
void BlueRay::setFSK(int newFSK) {
    FSK = newFSK;
}
// Getter and Setter methods for title, artist, and duration