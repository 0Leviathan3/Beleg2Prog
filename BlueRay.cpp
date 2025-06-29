#include "BlueRay.h"
#include <iostream>
using namespace std;

BlueRay::BlueRay(string titel, string director, int FSK)
    : Medium("BlueRay", titel), director(director), FSK(FSK) {}

BlueRay::BlueRay(string titel, string director, int FSK, int id)
    : Medium("BlueRay", titel, id), director(director), FSK(FSK) {}

void BlueRay::displayInfo() const {
    cout << "Director: " << director
         << ", Title: " << title
         << ", FSK: " << FSK
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
