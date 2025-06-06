
#include <iostream>
using namespace std;
#include "person.h"

Person::Person(string name, int age){
    this->name = name;
    this->age = age;
}
Person::Person(const Person& other){
    this->name = other.name;
    this->age = other.age;
}

// Ein Setter für den Namen, so fein,
// Aktualisiert den Namen, soll es sein.i
void Person::setName(const string& newName){
    name = newName;
}

// Ein Getter für den Namen, so klar,
// Gibt den Namen zurück, wunderbar.
string Person::getName() const{
    return name;
}

// Ein Setter für das Alter, genau,
// Aktualisiert das Alter, das ist schlau.
void Person::setAge(int newAge){
    age = newAge;
}

// Ein Getter für das Alter, so rein,
// Gibt das Alter zurück, soll es sein.
int Person::getAge() const{
    return age;
}
void Person::displayInfo() const{
    cout << "Name: " << name << ", Age: " << age << endl;
}
