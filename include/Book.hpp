#pragma once
#include <string>

class Book {
public:
    class Date {
    public:
        int year;
        Date() : year(0) {}
        Date(int y) : year(y) {}
    };

    std::string title;
    std::string author;
    int isbn;
    Date publishDate;
    bool isBorrowed;
    int borrowerId;

    Book();
    Book(std::string t, std::string a, int i, int y);

    bool borrow();
    void returnBook();
};
