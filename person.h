#ifndef PERSON_H
#define PERSON_H

#include "medium.h"
#include <string>

class Person : public Medium {

public:
    Person(const string& name, int age);
    Person(const Person& other);
    ~Person(); // Destructor
    void displayInfo() const;

private:
    string name;
    int age;
};;


#endif // PERSON_H