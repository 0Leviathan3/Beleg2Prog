#ifndef AUSLEIHMANAGER_H
#define AUSLEIHMANAGER_H

#include <vector>
#include <string>

using namespace std;

struct Ausleihe {
    int personenId;
    int mediumId;
};


class AusleihManager {
public:
static constexpr const char* DATEIPFAD = "../ausleihen.txt";
    static vector<Ausleihe> ladeAusleihenAusDatei();
    static bool speichereAusleihenInDatei(const vector<Ausleihe> &ausleihen, const string &pfad);

    static void fuegeAusleiheHinzu(vector<Ausleihe> &ausleihen, int personenId, int mediumId);
    static void entferneAusleihe(vector<Ausleihe> &ausleihen, int personenId, int mediumId);

    static bool istMediumAusgeliehen(const vector<Ausleihe>& ausleihen, int mediumId);
};

#endif // AUSLEIHMANAGER_H
