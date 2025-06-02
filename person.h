#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person{

public:
    Person(string name, int age);// Constructor
    Person(const Person& other);// Copy constructor
    void displayInfo() const;
    void setName(const string& newName);
    string getName() const;
    void setAge(int newAge);
    int getAge() const;

private:
    string name;
    int age;
};


#endif // PERSON_H