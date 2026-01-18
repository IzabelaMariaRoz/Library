#pragma once
#include "Person.hpp"
#include <iostream>

class Student : public Person { //klasa student dziedziczy po klasie person
public:
    int id;
    std::string address;
    int borrowedISBNs[3];
    int borrowedCount;

    Student(); //konstruktor
    Student(const std::string& f, const std::string& l, int id, const std::string& address);

    void introduce() override;
    bool borrowBook(int isbn);
    bool returnBook(int isbn);
    void showAccount();
};
