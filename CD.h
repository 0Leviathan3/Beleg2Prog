#ifndef CD_H
#define CD_H

#include "medium.h"
#include <string>

class CD : public Medium {

public:
    CD(string artist, string title, int duration);
    ~CD(); // Destructor
    void displayInfo() const;

private:
    int duration;
    string artist;
};

#endif // CD_H
