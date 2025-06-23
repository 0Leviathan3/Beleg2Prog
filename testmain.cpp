#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>
#include "medium.h"
#include "book.h"
#include "CD.h"
#include "BlueRay.h"
#include "person.h"
#include "datenbank.h"

using namespace std;
int main(){
    ifstream datei("mediumDb.txt");
    string line;
    vector<Medium*> medien;

    if (!datei.is_open()) {
        cerr << "Datei konnte nicht geöffnet werden." << endl;
        return 1; // Fehlercode
    }

    while (getline(datei, line)) {
        istringstream iss(line);
        string typ;

        if (getline(iss,typ, ';')){
            if (typ == "Book"){
                string titel, author,ISBN, ausgeliehen;
                if (getline(iss, titel, ';') && 
                    getline(iss, author, ';') &&
                    getline(iss, ISBN, ';')&&
                    getline(iss, ausgeliehen, ';')) {
                    bool ausgeliehenBool = (ausgeliehen == "true");
                    book *buch = new book(titel, ISBN, author);
                    buch->setAusgeliehen(ausgeliehenBool);
                    medien.push_back(buch);
                    cout << "Book: " << titel << ", Author: " << author << ", ISBN: " << ISBN << ausgeliehen << endl;
                } else {
                    cerr << "Fehler beim Lesen der Book-Daten." << endl;
                }
            } else if (typ == "BlueRay") {
                string titel, director, ausgeliehen,fskStr;
                int FSK;
                if (getline(iss, titel, ';') &&
                    getline(iss, director, ';') &&
                    getline(iss, fskStr, ';') &&
                    getline(iss, ausgeliehen, ';')){
                    FSK = stoi(fskStr);
                    bool ausgeliehenBool = (ausgeliehen == "true");
                    BlueRay *blueRay = new BlueRay(titel, director, FSK);
                    blueRay->setAusgeliehen(ausgeliehenBool);
                    medien.push_back(blueRay);
                    cout << "BlueRay: " << titel << ", Director: " << director << ", FSK: " << FSK << ausgeliehen << endl;
                } else {
                    cerr << "Fehler beim Lesen der BlueRay-Daten." << endl;
                }
            } else {
                cerr << "Unbekannter Medientyp: " << typ << endl;
            }
        }
    }

}