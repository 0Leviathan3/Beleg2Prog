#include "medium.h"
#include <iostream>
using namespace std;
#include "BlueRay.h"
BlueRay::BlueRay(const std::string& title, int resolution, int duration)
    : Medium(title), resolution(resolution), duration(duration) {}
BlueRay::~BlueRay() {
    cout << "Destructor called for BlueRay: " << title << endl;
}
void BlueRay::displayInfo() const {
    cout << "BlueRay: " << title << "\nResolution: " << resolution << "p\nDuration: " << duration << " minutes" << endl;
}