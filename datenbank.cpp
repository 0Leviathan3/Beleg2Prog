#include "datenbank.h"
#include "medium.h"
#include "book.h"
#include "BlueRay.h"
#include "person.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

// Funktion zum Schreiben einer Liste von Personen in eine Datei
bool Datenbank::schreibePersonenInDatei(const vector<Person>& personen, const string& dateiname) {
    // Öffnet die Datei eine Ebene über dem aktuellen Verzeichnis (z. B. außerhalb von /build)
    ofstream out(dateiname);
    
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
vector<Person> Datenbank::lesePersonenAusDatei(const string& dateiname) {
    vector<Person> personen;

    // Öffnet die Datei (eine Ebene höher)
    ifstream in(dateiname);

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
        string alterAlsString;

        if (getline(iss, name, ',') && getline(iss, alterAlsString)) {
            int alter = std::stoi(alterAlsString);  // String → int
            Person person(name, alter);
            personen.push_back(person);
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
// ----------------------------------------------------Medium----------------------------------------------------


bool Datenbank::schreibeMedienInDatei(const vector<Medium*>& medien, const string& dateiname) {
    ofstream out(dateiname);
    if (!out.is_open()) {
        cerr << "Datei konnte nicht geöffnet werden: " << dateiname << endl;
        return false;
    }

    for (const auto& medium : medien) {
        // Schreibe je nach Typ unterschiedlich (polymorph)
        string typ = medium->gettype();

        if (typ == "book") {
            book* buch = dynamic_cast<book*>(medium);
            if (buch) {
                out << "book;"
                    << buch->getTitle() << ";"
                    << buch->getAuthor() << ";"
                    << buch->getISBN() << ";"
                    << (buch->getAusgeliehen() ? "true" : "false") << "\n";
            }
        } else if (typ == "BlueRay") {
            BlueRay* br = dynamic_cast<BlueRay*>(medium);
            if (br) {
                out << "BlueRay;"
                    << br->getTitle() << ";"
                    << br->getDirector() << ";"
                    << br->getFSK() << ";"
                    << (br->getAusgeliehen() ? "true" : "false") << "\n";
            }
        } else {
            // Optional: weitere Medientypen oder Fehlerbehandlung
            cerr << "Unbekannter Medientyp beim Schreiben: " << typ << endl;
        }
    }

    return true;
}

// Lesen der Medien aus Datei
vector<Medium*> Datenbank::leseMedienAusDatei(const string& dateiname) {
    vector<Medium*> medien;
    ifstream in(dateiname);
    if (!in.is_open()) {
        cerr << "Datei konnte nicht geöffnet werden: " << dateiname << endl;
        return medien;
    }

    string line;
    while (getline(in, line)) {
        istringstream iss(line);
        string typ;
        if (getline(iss, typ, ';')) {
            // 🧼 Typ bereinigen: Leerzeichen, \r, \n entfernen
            typ.erase(remove_if(typ.begin(), typ.end(), [](char c) {
                return c == '\r' || c == '\n' || isspace(c);
            }), typ.end());
        
            if (typ == "Book") {
                string titel, autor, isbn, ausgeliehenStr;
                if (getline(iss, titel, ';') && getline(iss, autor, ';') &&
                    getline(iss, isbn, ';') && getline(iss, ausgeliehenStr)) {
        
                    book* buch = new book(titel, isbn, autor);
                    buch->setAusgeliehen(ausgeliehenStr == "true");
                    medien.push_back(buch);
                } else {
                    cerr << "Fehler beim Lesen der book-Daten." << endl;
                }
            } else if (typ == "BlueRay") {
                string titel, director, fskStr, ausgeliehenStr;
                if (getline(iss, titel, ';') && getline(iss, director, ';') &&
                    getline(iss, fskStr, ';') && getline(iss, ausgeliehenStr)) {
        
                    int fsk = stoi(fskStr);
                    BlueRay* br = new BlueRay(titel, director, fsk);
                    br->setAusgeliehen(ausgeliehenStr == "true");
                    medien.push_back(br);
                } else {
                    cerr << "Fehler beim Lesen der BlueRay-Daten." << endl;
                }
            } else {
                cerr << "Unbekannter Medientyp beim Lesen: [" << typ << "]" << endl;
            }
        }
        
    }
    return medien;
}

// Löschen von Medien anhand ihrer Indizes
void Datenbank::loescheMedien(vector<Medium*>& medien, const vector<int>& zuLoeschendeIndizes) {
    vector<int> sortedIndices = zuLoeschendeIndizes;
    sort(sortedIndices.rbegin(), sortedIndices.rend());
    for (int idx : sortedIndices) {
        if (idx >= 0 && idx < static_cast<int>(medien.size())) {
            delete medien[idx];  // Speicher freigeben, da new verwendet
            medien.erase(medien.begin() + idx);
        }
    }
}