#include "ausleihmanager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

vector<Ausleihe> AusleihManager::ladeAusleihenAusDatei() {
    vector<Ausleihe> ausleihen;
    ifstream datei(DATEIPFAD);
    string zeile;

    while (getline(datei, zeile)) {
        istringstream iss(zeile);
        string personIdStr, mediumIdStr;

        if (getline(iss, personIdStr, ';') && getline(iss, mediumIdStr)) {
            Ausleihe a;
            a.personenId = stoi(personIdStr);
            a.mediumId = stoi(mediumIdStr);
            ausleihen.push_back(a);
        }
    }

    return ausleihen;
}

bool AusleihManager::speichereAusleihenInDatei(const vector<Ausleihe> &ausleihen, const string &pfad) {
    ofstream datei(pfad);
    if (!datei.is_open()) return false;

    for (const auto& a : ausleihen) {
        datei << a.personenId << ";" << a.mediumId << "\n";
    }

    return true;
}

void AusleihManager::fuegeAusleiheHinzu(vector<Ausleihe> &ausleihen, int personenId, int mediumId) {
    ausleihen.push_back({personenId, mediumId});
}

void AusleihManager::entferneAusleihe(vector<Ausleihe> &ausleihen, int personenId, int mediumId) {
    ausleihen.erase(remove_if(ausleihen.begin(), ausleihen.end(),
        [personenId, mediumId](const Ausleihe& a) {
            return a.personenId == personenId && a.mediumId == mediumId;
        }), ausleihen.end());
}

bool AusleihManager::istMediumAusgeliehen(const vector<Ausleihe>& ausleihen, int mediumId) {
    for (const auto& a : ausleihen) {
        if (a.mediumId == mediumId)
            return true;
    }
    return false;
}
