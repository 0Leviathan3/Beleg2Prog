#ifndef CD_H
#define CD_H

#include "medium.h"
#include <string>

class CD : public Medium {

public:
    CD(string artist, string title, int duration);
    ~CD(); // Destructor
    void displayInfo() const;
    string getTitle();
    string getArtist();
    int getDuration() const;
    void setTitle(const string& newTitle);
    void setArtist(const string& newArtist);
    void setDuration(int newDuration);
    
    // Getter and Setter methods for title, artist, and duration
private:
    int duration;
    string artist;
};

#endif // CD_H
