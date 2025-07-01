#include "datenbank.h"
#include "book.h"
#include "BlueRay.h"
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
        out << p.getName() << "," << p.getAge() << "," << p.getId() << "\n";
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
        string name, alterAlsString, idStr;
        if (getline(iss, name, ',') && getline(iss, alterAlsString, ',') && getline(iss, idStr)) {
            int alter = stoi(alterAlsString);
            int id = stoi(idStr);
            Person person(name, alter, id); // Konstruktor mit ID
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
                    << (buch->getAusgeliehen() ? "true" : "false") << ";"
                    << buch->getId() << "\n";
            }
        } else if (typ == "BlueRay") {
            BlueRay* br = dynamic_cast<BlueRay*>(medium);
            if (br) {
                out << "BlueRay;"
                    << br->getTitle() << ";"
                    << br->getDirector() << ";"
                    << br->getFSK() << ";"
                    << (br->getAusgeliehen() ? "true" : "false") << ";"
                    << br->getId() << "\n";
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
            typ.erase(remove_if(typ.begin(), typ.end(), [](char c) {
                return c == '\r' || c == '\n' || isspace(c);
            }), typ.end());

            if (typ == "Book") {
                string titel, autor, isbn, ausgeliehenStr, idStr;
                if (getline(iss, titel, ';') && getline(iss, autor, ';') &&
                    getline(iss, isbn, ';') && getline(iss, ausgeliehenStr, ';') &&
                    getline(iss, idStr)) {

                    int id = stoi(idStr);
                    // Autor und ISBN beim Konstruktor tauschen, weil in Datei: Titel;Autor;ISBN
                    book* buch = new book(titel, autor, isbn, id);
                    buch->setAusgeliehen(ausgeliehenStr == "true");
                    medien.push_back(buch);
                } else {
                    cerr << "Fehler beim Lesen der Book-Daten." << endl;
                }
            } else if (typ == "BlueRay") {
                string titel, director, fskStr, ausgeliehenStr, idStr;
                if (getline(iss, titel, ';') && getline(iss, director, ';') &&
                    getline(iss, fskStr, ';') && getline(iss, ausgeliehenStr, ';') &&
                    getline(iss, idStr)) {

                    int fsk = stoi(fskStr);
                    int id = stoi(idStr);
                    BlueRay* br = new BlueRay(titel, director, fsk, id);
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

    // nextId für Medien richtig setzen, um doppelte IDs zu vermeiden
    int maxId = 0;
    for (const auto& m : medien) {
        if (m->getId() > maxId)
            maxId = m->getId();
    }
    Medium::setNextId(maxId + 1);

    return medien;
}

void Datenbank::loescheMedien(vector<Medium*>& medien, const vector<int>& zuLoeschendeIndizes) {
    vector<int> sortedIndices = zuLoeschendeIndizes;
    sort(sortedIndices.rbegin(), sortedIndices.rend());
    for (int idx : sortedIndices) {
        if (idx >= 0 && idx < static_cast<int>(medien.size())) {
            delete medien[idx];
            medien.erase(medien.begin() + idx);
        }
    }
}
