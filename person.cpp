#include "medium.h"
#include <iostream>
using namespace std;
#include "person.h"

Person::Person(const string& name, int age) : name(name), age(age) {}

void Person::displayInfo() const {
    cout << "Name: " << name << "\nAge: " << age << endl;
}
Person::~Person() {
    cout << "Destructor called for Person: " << name << endl;
}