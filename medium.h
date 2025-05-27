#ifndef MEDIUM_H
#define MEDIUM_H
#include <string>

class Medium {
public:
    Medium(string titel, string autor, string genre);
    virtual ~Medium();
    virtual void displayDetails();
    string getTitle() const;
    string getAutor() const;
    int getId() const;
    string getGenre() const;
    void setTitle(const string& newTitle);
    void setAutor(const string& newAutor);
    void setId(int newId);
    void setGenre(const string& newGenre);

protected:
    string title;
    string autor;
    int id; // Unique identifier for each medium
    static int nextId; // Static member to keep track of the next ID
    string genre;
};

#endif // MEDIUM_H