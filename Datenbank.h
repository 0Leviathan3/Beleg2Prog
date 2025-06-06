#ifndef DATENBANK_H
#define DATENBANK_H

#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "person.h" // Assuming Person class is defined in person.h

class Datenbank {
    std::string dateiname;

public:
    explicit Datenbank(const std::string& fname);

    void speichern(const Person& p);
    void loeschen(const std::string& name);
};

#endif // DATENBANK_H