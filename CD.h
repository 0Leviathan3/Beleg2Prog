#ifndef CD_H
#define CD_H

#include "medium.h"
#include <string>

class CD : public Medium {

public:
    CD(const string& artist, const string& title, int duration);
    ~CD(); // Destructor
    void displayInfo() const;

private:
    string artist;
    string title;
    int duration;
};

#endif // CD_H
