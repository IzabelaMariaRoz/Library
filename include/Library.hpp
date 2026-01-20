#pragma once
#include "Book.hpp"
#include "Student.hpp"
#include <string>

class Library {
public:
    static const int MAX_BOOKS = 15; //wartosc globalna dla wszystkich studentow np
    static const int MAX_STUDENTS = 5;

    Book books[MAX_BOOKS];
    Student students[MAX_STUDENTS];
    int bookCount;
    int studentCount;

    Library(); //deklaracja konst

    void saveData(); //metody
    void loadData();
    void generateReport();
};
