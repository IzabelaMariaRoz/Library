#pragma once
#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int isbn;
    int yearOfPublishing;
    bool isBorrowed;

public:
    Book();
    Book(const std::string& title, const std::string& author, int isbn, int year);

    std::string getTitle() const;
    std::string getAuthor() const;
    int getISBN() const;
    int getYear() const;
    bool getBorrowedStatus() const;

    void borrow();
    void returnBook();

    std::string serialize() const;
    void deserialize(const std::string& data);
};
