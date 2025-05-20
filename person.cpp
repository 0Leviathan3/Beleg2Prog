#include "medium.h"
#include <iostream>
using namespace std;
#include "person.h"

Person::Person(const char* name, int age) : name(name), age(age) {}
Person::Person(const Person& other) {
    name = other.name;
    age = other.age;
}

void Person::displayInfo() const {
    cout << "Name: " << name << "\nAge: " << age << endl;
}
Person::~Person() {
    cout << "Destructor called for Person: " << name << endl;
}