/*Studeingruppe 24/041/63
Levin Grune
Matr Nr 56127 */

#ifndef AUSLEIHMANAGER_H
#define AUSLEIHMANAGER_H

#include <vector>
#include <string>

struct Ausleihe {
    std::string personenName;
    std::string mediumTitel;
};

class AusleihManager {
public:
    static std::vector<Ausleihe> ladeAusleihenAusDatei(const std::string &pfad);
    static bool speichereAusleihenInDatei(const std::vector<Ausleihe> &ausleihen, const std::string &pfad);
    static void fuegeAusleiheHinzu(std::vector<Ausleihe> &ausleihen, const std::string &personenName, const std::string &mediumTitel);
    static void entferneAusleihe(std::vector<Ausleihe> &ausleihen, const std::string &personenName, const std::string &mediumTitel);
static bool istMediumAusgeliehen(const std::vector<Ausleihe> &ausleihen, const std::string &mediumTitel);
};

#endif // AUSLEIHMANAGER_H
