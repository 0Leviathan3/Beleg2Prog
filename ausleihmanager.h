#ifndef AUSLEIHMANAGER_H
#define AUSLEIHMANAGER_H

#include <vector>
#include <string>

struct Ausleihe {
    int personenId;
    int mediumId;
};

class AusleihManager {
public:
    static constexpr const char* DATEIPFAD = "../ausleihen.txt";

    static std::vector<Ausleihe> ladeAusleihenAusDatei();
    static bool speichereAusleihenInDatei(const std::vector<Ausleihe> &ausleihen, const std::string &pfad = DATEIPFAD);

    static void fuegeAusleiheHinzu(std::vector<Ausleihe> &ausleihen, int personenId, int mediumId);
    static void entferneAusleihe(std::vector<Ausleihe> &ausleihen, int personenId, int mediumId);

    static bool istMediumAusgeliehen(const std::vector<Ausleihe>& ausleihen, int mediumId);
};

#endif // AUSLEIHMANAGER_H
