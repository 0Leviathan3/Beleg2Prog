/*Studeingruppe 24/041/63
Levin Grune
Matr Nr 56127 */

#ifndef MEDIUM_H
#define MEDIUM_H

#include <string>
using namespace std;

class Medium {
public:
    Medium(string type, string titel);                  
    Medium(string type, string titel, int id);          

    virtual void displayDetails();
    string getTitle() const;
    string gettype() const;
    int getId() const;
    bool getAusgeliehen();

    void setTitle(const string& newTitle);
    void settype(const string& newtype);
    void setId(int newId);
    void setAusgeliehen(bool ausgeliehen);

    static void setNextId(int id); 

protected:
    string title;
    int id;
    string type;
    bool ausgehlihen = false;
    static int nextId;
};

#endif // MEDIUM_H
