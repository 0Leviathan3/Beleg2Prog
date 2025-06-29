
#include <iostream>
using namespace std;
#include "person.h"


int Person::nextId = 1;

Person::Person(std::string name, int age, int id) 
    : name(std::move(name)), age(age) 
{
    if (id == -1) {
        this->id = nextId++;
    } else {
        this->id = id;
        if (id >= nextId) {
            nextId = id + 1;
        }
    }
}

Person::Person(const Person& other) {
    this->name = other.name;
    this->age = other.age;
    this->id = nextId++;
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
    cout <<"ID:" << id<< "Name: " << name << ", Age: " << age << endl;
}
int Person::getId() const {
    return id;
}
