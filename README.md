# Medienbibliothek

## Projektübersicht

Die Medienbibliothek ist eine Desktop-Anwendung zur Verwaltung von Medien, Personen und Ausleihen.  
Sie wurde in C++ mit dem Qt-Framework entwickelt und bietet eine einfache Benutzeroberfläche für die Verwaltung und Anzeige von Medieninhalten sowie die Zuordnung von Ausleihen an Personen.

---

## Features

- **Startseite:** Übersichtliche Willkommensseite mit Erläuterung der Menü-Buttons  
- **Medien Anzeige:** Übersicht und Verwaltung aller verfügbaren Medien  
- **Personenverwaltung:** Verwaltung der registrierten Personen  
- **Ausleihen:** Übersicht und Verwaltung der Ausleihen von Medien an Personen  

---

## Aufbau

Die Anwendung nutzt ein `QStackedWidget`, um zwischen folgenden Seiten zu wechseln:

- **Hauptmenü / Startseite:** Willkommenstext und kurze Erklärung der Buttons  
- **Eingabe:** Eingabemaske für neue Medien oder Personen  
- **Ausgabetabelle:** Tabellarische Übersicht der vorhandenen Personen  
- **Ausleihanzeige:** Anzeige und Verwaltung der aktuellen Ausleihen  

---

## Ausleihen: Hinzufügen und Löschen

### Ausleihe hinzufügen

1. Im Tab **„Ausleihanzeige“** auf **„Hinzufügen“** klicken.  
2. Es öffnet sich ein Dialogfenster zur Auswahl von **Person** und **Medium**.  
3. Nach Auswahl und Bestätigung wird die Ausleihe in die Datei geschrieben.  
4. Die Tabelle wird automatisch aktualisiert.

### Ausleihe löschen

- In der Tabelle eine **Zeile anklicken**, um die gewünschte Ausleihe auszuwählen.  
- Auf **„Löschen“** klicken.  
- Die Ausleihe wird aus der Datei entfernt und die Tabelle neu geladen.
---

## Personenverwaltung: Hinzufügen und Löschen

### Person hinzufügen

1. Im Tab **„Eingabe“** auf **„Neuhinzufügen“** klicken.  
2. Im Dialogfeld den **Namen** und das **Alter** der Person eingeben.  
3. Mit **„Hinzufügen“** bestätigen.  
4. Die Person erscheint in der Tabelle und wird gespeichert.

### Person löschen

- In der Tabelle eine **Zeile anklicken**, um die gewünschte Person auszuwählen.  
- Auf **„Ausgewählte löschen“** klicken.  
- Die Person wird aus der Datei entfernt und die Tabelle wird aktualisiert.

---

## Medienverwaltung: Hinzufügen und Löschen

### Medium hinzufügen

1. Im Tab **„Eingabe“** auf **„Neuhinzufügen“** klicken.  
2. Im Dialog den **Medientyp** auswählen (z. B. *Book* oder *BlueRay*).  
3. **Titel**, **Autor/Regisseur** sowie **ISBN/FSK** eingeben.  
4. Auf **„Hinzufügen“** klicken.  
5. Das Medium wird gespeichert und erscheint in der Übersicht.

### Medium löschen

- In der Tabelle eine **Zeile anklicken**, um das gewünschte Medium auszuwählen.  
- Auf **„Ausgewählte löschen“** klicken.  
- Das Medium wird entfernt und die Tabelle wird aktualisiert.



## Installation und Kompilierung

1. Qt (Version 6 empfohlen) installieren: [https://www.qt.io/download](https://www.qt.io/download)  
2. Projekt klonen oder Dateien herunterladen  
3. Projekt in Qt Creator öffnen  
4. Build & Run starten  

Alternativ über CMake und Kommandozeile:

```bash
mkdir build
cd build
cmake ..
make
./Medienbibliothek
