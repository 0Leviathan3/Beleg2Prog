
#ifndef BLUERAY_H
#define BLUERAY_H

#include "medium.h"
#include <string>

class BlueRay : public Medium {

public:
    BlueRay(const std::string& title, int resolution, int duration);
    ~BlueRay(); // Destructor
    void displayInfo() const;

private:
    std::string title;
    int resolution;
    int duration;
};

#endif // BLUERAY_H