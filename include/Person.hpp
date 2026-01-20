#pragma once
#include <string>
#include <iostream>

//kl. abst. bo istnieje metoda czysto wirtualna.
class Person {
public:
    std::string firstName;
    std::string lastName;

    Person() {} //konstruktor
    Person(const std::string& f, const std::string& l) 
        : firstName(f), lastName(l) {}

    virtual void introduce() = 0; // czysto wirtualna funkcja. Każda klasa dziedz. po Person musi nadpisać metodę introduce()
    virtual ~Person() {} // wirtualny destruktor dla bezpieczeństwa polimorfizmu
};
