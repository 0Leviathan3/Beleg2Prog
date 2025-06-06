#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person{

public:
    Person(std::string name, int age);// Constructor
    Person(const Person& other);// Copy constructor
    void displayInfo() const;
    void setName(const std::string& newName);
    std::string getName() const;
    void setAge(int newAge);
    int getAge() const;

private:
    std::string name;
    int age;
};


#endif // PERSON_H