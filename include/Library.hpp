#pragma once
#include "Book.hpp"
#include "Student.hpp"
#include <string>

class Library {
public:
    static const int MAX_BOOKS = 100; //wartosc globalna dla wszystkich studentow np
    static const int MAX_STUDENTS = 100;

    Book books[MAX_BOOKS];
    Student students[MAX_STUDENTS];
    int bookCount;
    int studentCount;

    Library(); //konst

    void saveData(); //metody
    void loadData();
    void generateReport();
};
