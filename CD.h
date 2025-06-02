#ifndef CD_H
#define CD_H

#include "medium.h"
#include <string>

class CD : public Medium {
public:
    CD(string artist, string title, int duration, string album);
    void displayInfo() const;
    int getDuration() const;
    string getArtist();
    string getAlbum();
    void setDuration(int newDuration);
    void setArtist(const string& newArtist);
    void setAlbum(const string& newAlbum);

private:
int duration; // Duration of the CD in minutes
string artist; // Artist of the CD
string album; // Album of the CD
};

#endif // CD_H
