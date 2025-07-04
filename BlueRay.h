/*Studeingruppe 24/041/63
Levin Grune
Matr Nr 56127 */

#ifndef BLUERAY_H
#define BLUERAY_H

#include "medium.h"
#include <string>

class BlueRay : public Medium {
public:
    BlueRay(string titel, string director, int FSK);
    BlueRay(string titel, string director, int FSK, int id); 
    
    void displayInfo() const;
    string getDirector() const;
    int getFSK() const;
    void setDirector(const string& newDirector);
    void setFSK(int newFSK);

private:
    string director;
    int FSK;
};

#endif // BLUERAY_H
