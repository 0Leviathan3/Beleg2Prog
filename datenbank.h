#ifndef DATENBANK_H
#define DATENBANK_H

#include <vector>
#include <string>
#include "person.h"
#include "medium.h"

class Datenbank {
    

public:
// Für Personen
    static bool schreibePersonenInDatei(const std::vector<Person>& personen,const std::string& dateiname);
    static std::vector<Person> lesePersonenAusDatei(const std::string& dateiname);
    static void loeschePersonen(std::vector<Person>& personen, const std::vector<int>& zuLoeschendeIndizes);

// Für Medien
    static bool schreibeMedienInDatei(const std::vector<Medium*>& medien, const std::string& dateiname);
    static std::vector<Medium*> leseMedienAusDatei(const std::string& dateiname);
    static void loescheMedien(std::vector<Medium*>& medien, const std::vector<int>& zuLoeschendeIndizes);

};

#endif // DATENBANK_H
