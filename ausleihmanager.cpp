#include "ausleihmanager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

std::vector<Ausleihe> AusleihManager::ladeAusleihenAusDatei(const std::string &pfad) {
    std::vector<Ausleihe> ausleihen;
    std::ifstream datei(pfad);
    if (!datei.is_open()) return ausleihen;

    std::string zeile;
    while (std::getline(datei, zeile)) {
        std::istringstream iss(zeile);
        std::string personenName, mediumTitel;

        if (std::getline(iss, personenName, ';') && std::getline(iss, mediumTitel)) {
            Ausleihe a{personenName, mediumTitel};
            ausleihen.push_back(a);
        }
    }
    return ausleihen;
}

bool AusleihManager::speichereAusleihenInDatei(const std::vector<Ausleihe> &ausleihen, const std::string &pfad) {
    std::ofstream datei(pfad);
    if (!datei.is_open()) return false;

    for (const auto &a : ausleihen) {
        datei << a.personenName << ";" << a.mediumTitel << "\n";
    }
    return true;
}

void AusleihManager::fuegeAusleiheHinzu(std::vector<Ausleihe> &ausleihen, const std::string &personenName, const std::string &mediumTitel) {
    ausleihen.emplace_back(Ausleihe{personenName, mediumTitel});
}

void AusleihManager::entferneAusleihe(std::vector<Ausleihe> &ausleihen, const std::string &personenName, const std::string &mediumTitel) {
    ausleihen.erase(std::remove_if(ausleihen.begin(), ausleihen.end(),
                                  [&](const Ausleihe &a) {
                                      return a.personenName == personenName && a.mediumTitel == mediumTitel;
                                  }),
                    ausleihen.end());
}

bool AusleihManager::istMediumAusgeliehen(const std::vector<Ausleihe> &ausleihen, const std::string &mediumTitel) {
    return std::any_of(ausleihen.begin(), ausleihen.end(),
                       [&](const Ausleihe &a) { return a.mediumTitel == mediumTitel; });
}
