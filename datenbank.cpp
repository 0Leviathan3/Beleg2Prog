#include "Datenbank.h"

Datenbank::Datenbank(const std::string& fname) : dateiname(fname) {}

void Datenbank::speichern(const Person& p) {
    std::ofstream file(dateiname, std::ios::app);
    if (file.is_open()) {
        file << p.to_string() << "\n";
        file.close();
    } else {
        std::cerr << "Fehler: Datei konnte nicht geöffnet werden." << std::endl;
    }
}

void Datenbank::loeschen(const std::string& name) {
    std::ifstream infile(dateiname);
    std::vector<std::string> zeilen;
    std::string line;

    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            if (line.find(name + ",") != 0) { // nur behalten, wenn Name nicht am Anfang steht
                zeilen.push_back(line);
            }
        }
        infile.close();

        std::ofstream outfile(dateiname, std::ios::trunc); // Datei leeren
        if (outfile.is_open()) {
            for (const auto& z : zeilen) {
                outfile << z << "\n";
            }
            outfile.close();
        } else {
            std::cerr << "Fehler: Datei konnte nicht geöffnet werden." << std::endl;
        }
    } else {
        std::cerr << "Fehler: Datei konnte nicht geöffnet werden." << std::endl;
    }
}