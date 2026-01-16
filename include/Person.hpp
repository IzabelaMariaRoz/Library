#pragma once
#include <string>
#include <iostream>

class Person {
public:
    std::string firstName;
    std::string lastName;

    Person() {}
    Person(const std::string& f, const std::string& l) 
        : firstName(f), lastName(l) {}

    virtual void introduce() = 0; // czysto wirtualna funkcja
    virtual ~Person() {} // wirtualny destruktor dla bezpieczeństwa polimorfizmu
};
