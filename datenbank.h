#ifndef DATENBANK_H
#define DATENBANK_H

#include <vector>
#include <string>
#include "person.h"

class Datenbank {
    

public:
    static bool schreibePersonenInDatei(const std::vector<Person>& personen);
    static std::vector<Person> lesePersonenAusDatei();
    static void loeschePersonen(std::vector<Person>& personen, const std::vector<int>& zuLoeschendeIndizes);
};

#endif // DATENBANK_H
