
#ifndef BLUERAY_H
#define BLUERAY_H

#include "medium.h"
#include <string>

class BlueRay : public Medium {

public:
   BlueRay(string director, string title, int duration, int FSK);
    void displayInfo() const;
    int getDuration() const;
    string getDirector() const;
    int getFSK() const;
    void setDuration(int newDuration);
    void setDirector(const string& newDirector);
    void setFSK(int newFSK);

private:
    string director;
    int duration;
    int FSK;

};

#endif // BLUERAY_H