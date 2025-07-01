#include "ausleihmanager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

std::vector<Ausleihe> AusleihManager::ladeAusleihenAusDatei() {
    std::vector<Ausleihe> ausleihen;
    std::ifstream datei(DATEIPFAD);
    if (!datei.is_open()) return ausleihen;

    std::string zeile;
    while (std::getline(datei, zeile)) {
        std::istringstream iss(zeile);
        std::string personIdStr, mediumIdStr;

        if (std::getline(iss, personIdStr, ';') && std::getline(iss, mediumIdStr)) {
            Ausleihe a;
            a.personenId = std::stoi(personIdStr);
            a.mediumId = std::stoi(mediumIdStr);
            ausleihen.push_back(a);
        }
    }
    return ausleihen;
}

bool AusleihManager::speichereAusleihenInDatei(const std::vector<Ausleihe> &ausleihen, const std::string &pfad) {
    std::ofstream datei(pfad);
    if (!datei.is_open()) return false;

    for (const auto& a : ausleihen) {
        datei << a.personenId << ";" << a.mediumId << "\n";
    }
    return true;
}

void AusleihManager::fuegeAusleiheHinzu(std::vector<Ausleihe> &ausleihen, int personenId, int mediumId) {
    ausleihen.push_back({personenId, mediumId});
}

void AusleihManager::entferneAusleihe(std::vector<Ausleihe> &ausleihen, int personenId, int mediumId) {
    ausleihen.erase(std::remove_if(ausleihen.begin(), ausleihen.end(),
        [personenId, mediumId](const Ausleihe& a) {
            return a.personenId == personenId && a.mediumId == mediumId;
        }), ausleihen.end());
}

bool AusleihManager::istMediumAusgeliehen(const std::vector<Ausleihe>& ausleihen, int mediumId) {
    for (const auto& a : ausleihen) {
        if (a.mediumId == mediumId)
            return true;
    }
    return false;
}
