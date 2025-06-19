#include "datenbank.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

// Funktion zum Schreiben einer Liste von Personen in eine Datei
bool Datenbank::schreibePersonenInDatei(const vector<Person>& personen) {
    // Öffnet die Datei eine Ebene über dem aktuellen Verzeichnis (z. B. außerhalb von /build)
    ofstream out("../beispiel.txt");
    
    // Prüft, ob die Datei erfolgreich geöffnet wurde
    if (!out.is_open()) {
        cerr << "Datei konnte nicht geöffnet werden: beispiel.txt" << endl;
        return false;
    }

    // Schreibt jede Person als "Name,Alter" in die Datei
    for (const auto& p : personen) {
        out << p.getName() << "," << p.getAge() << "\n";
    }

    return true;  // Erfolgreich gespeichert
}

// Funktion zum Lesen einer Liste von Personen aus der Datei
vector<Person> Datenbank::lesePersonenAusDatei() {
    vector<Person> personen;

    // Öffnet die Datei (eine Ebene höher)
    ifstream in("../beispiel.txt");

    // Prüft, ob die Datei geöffnet werden konnte
    if (!in.is_open()) {
        cerr << "Datei konnte nicht geöffnet werden: beispiel.txt" << endl;
        return personen;  // Gibt leere Liste zurück
    }

    string line;
    // Liest die Datei Zeile für Zeile
    while (getline(in, line)) {
        istringstream iss(line);
        string name;
        int alter;

        // Trennt die Zeile am Komma in Name und Alter
        if (getline(iss, name, ',') && (iss >> alter)) {
            // Fügt die Person zur Liste hinzu
            personen.emplace_back(name, alter);
        }
    }

    return personen;  // Gibt die gelesene Liste zurück
}

// Funktion zum Löschen bestimmter Personen anhand ihrer Indizes
void Datenbank::loeschePersonen(vector<Person>& personen, const vector<int>& zuLoeschendeIndizes) {
    // Kopiert die Indizes und sortiert sie in umgekehrter Reihenfolge (damit das Löschen von hinten erfolgt)
    vector<int> sortedIndices = zuLoeschendeIndizes;
    sort(sortedIndices.rbegin(), sortedIndices.rend());

    // Löscht die Personen an den angegebenen Indizes
    for (int idx : sortedIndices) {
        if (idx >= 0 && idx < static_cast<int>(personen.size())) {
            personen.erase(personen.begin() + idx);
        }
    }
}
