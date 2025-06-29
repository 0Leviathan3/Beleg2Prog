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

// --- Personen ---

bool Datenbank::schreibePersonenInDatei(const vector<Person>& personen, const string& dateiname) {
    ofstream out(dateiname);
    if (!out.is_open()) {
        cerr << "Datei konnte nicht geöffnet werden: " << dateiname << endl;
        return false;
    }
    for (const auto& p : personen) {
        out << p.getName() << "," << p.getAge() << "\n";
    }
    return true;
}

vector<Person> Datenbank::lesePersonenAusDatei(const string& dateiname) {
    vector<Person> personen;
    ifstream in(dateiname);
    if (!in.is_open()) {
        cerr << "Datei konnte nicht geöffnet werden: " << dateiname << endl;
        return personen;
    }
    string line;
    while (getline(in, line)) {
        istringstream iss(line);
        string name;
        string alterAlsString;
        if (getline(iss, name, ',') && getline(iss, alterAlsString)) {
            int alter = stoi(alterAlsString);
            Person person(name, alter);
            personen.push_back(person);
        }
    }
    return personen;
}

void Datenbank::loeschePersonen(vector<Person>& personen, const vector<int>& zuLoeschendeIndizes) {
    vector<int> sortedIndices = zuLoeschendeIndizes;
    sort(sortedIndices.rbegin(), sortedIndices.rend());
    for (int idx : sortedIndices) {
        if (idx >= 0 && idx < static_cast<int>(personen.size())) {
            personen.erase(personen.begin() + idx);
        }
    }
}

// --- Medien ---

bool Datenbank::schreibeMedienInDatei(const vector<Medium*>& medien, const string& dateiname) {
    ofstream out(dateiname);
    if (!out.is_open()) {
        cerr << "Datei konnte nicht geöffnet werden: " << dateiname << endl;
        return false;
    }
    for (const auto& medium : medien) {
        string typ = medium->gettype();  
        if (typ == "Book") {
            book* buch = dynamic_cast<book*>(medium);
            if (buch) {
                out << "Book;"
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
            cerr << "Unbekannter Medientyp beim Schreiben: " << typ << endl;
        }
    }
    return true;
}

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
            // Typ bereinigen: Leerzeichen, \r, \n entfernen
            typ.erase(remove_if(typ.begin(), typ.end(), [](char c) {
                return c == '\r' || c == '\n' || isspace(c);
            }), typ.end());

            if (typ == "Book") {
                string titel, autor, isbn, ausgeliehenStr;
                if (getline(iss, titel, ';') && getline(iss, autor, ';') &&
                    getline(iss, isbn, ';') && getline(iss, ausgeliehenStr)) {

                    book* buch = new book(titel,isbn, autor);
                    buch->setAusgeliehen(ausgeliehenStr == "true");
                    medien.push_back(buch);
                } else {
                    cerr << "Fehler beim Lesen der Book-Daten." << endl;
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

void Datenbank::loescheMedien(vector<Medium*>& medien, const vector<int>& zuLoeschendeIndizes) {
    vector<int> sortedIndices = zuLoeschendeIndizes;
    sort(sortedIndices.rbegin(), sortedIndices.rend());
    for (int idx : sortedIndices) {
        if (idx >= 0 && idx < static_cast<int>(medien.size())) {
            delete medien[idx];  // Speicher freigeben, da new verwendet wurde
            medien.erase(medien.begin() + idx);
        }
    }
}
