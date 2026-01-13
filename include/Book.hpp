#pragma once
#include <string>
#include <sstream>
using namespace std;

class Book {
private:
    string title;
    string author;
    int isbn;
    int yearOfPublishing;
    int quantity;        //ile egze. biblioteka posiada
    int borrowedCount;    //aktualnie wypożyczonych

public:
    // Konstruktor domyślny
    Book() : title(""), author(""), isbn(0), yearOfPublishing(0), quantity(1), borrowedCount(0) {}
    //konstruktor pełny
    Book(const string& title, const string& author, int isbn, int year, int quantity = 1)
        : title(title), author(author), isbn(isbn), yearOfPublishing(year), quantity(quantity), borrowedCount(0) {}



      //getter
    string getTitle() const{return title;}
    string getAuthor() const{return author;}
    int getISBN() const{return isbn;}
    int getYear() const{return yearOfPublishing;}
    int getQuantity() const{return quantity;}
    int getBorrowedCount() const { return borrowedCount; }
    int getAvailable() const{return quantity - borrowedCount;}

    bool borrow();
    void returnBook();
    void searchByTitleInFile(const string& filename, const string& titleQuery);
    void searchByAuthorInFile(const string& filename, const string& authorQuery);


};
