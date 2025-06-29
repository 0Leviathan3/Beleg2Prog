#ifndef MEDIUM_H
#define MEDIUM_H
#include <string>
using namespace std; // warum auch immer aber muss dort stehen 

class Medium {
public:
    Medium(string type, string title, int id);// Constructor with title and type
    virtual void displayDetails();
    string getTitle() const;
    string getAutor() const;
    int getId() const;
    string gettype() const;
    void setTitle(const string& newTitle);
    void setAutor(const string& newAutor);
    void setId(int newId);
    void settype(const string& newtype);
    bool getAusgeliehen();
    void setAusgeliehen(bool ausgeliehen);

protected:
    string title;
    int id; // Unique identifier for each medium
    static int nextId; 
    string type;
    bool ausgehlihen; // Indicates if the medium is currently borrowed
};

#endif // MEDIUM_H