#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person{

public:
    Person(std::string name, int age, int id);// Constructor
    Person(const Person& other);// Copy constructor
    void displayInfo() const;
    void setName(const std::string& newName);
    std::string getName() const;
    void setAge(int newAge);
    int getAge() const;
    int getId() const;  

private:
    std::string name;
    int age;
    int id;
};


#endif // PERSON_H