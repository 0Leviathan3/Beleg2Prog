#include <iostream>
#include <fstream>

int main() {
    std::ofstream datei("beispiel.txt"); // Datei öffnen (oder erstellen)

    if (datei.is_open()) {
        datei << "Hallo Welt!\n";
        datei << "Noch eine Zeile.\n";
        datei.close(); // Datei schließen
    } else {
        std::cerr << "Fehler beim Öffnen der Datei.\n";
    }

    return 0;
}