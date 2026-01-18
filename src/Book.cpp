#include "Book.hpp"

Book::Book() {  //kostruktor klasy book poza klasa
    isbn = 0;
    isBorrowed = false;
    borrowerId = 0;
}

Book::Book(std::string t, std::string a, int i, int y) {
    title = t;
    author = a;
    isbn = i;
    publishDate = Date(y);
    isBorrowed = false;
    borrowerId = 0;
}

bool Book::borrow() {
    if (!isBorrowed) {
        isBorrowed = true;
        return true;
    }
    return false;
}

void Book::returnBook() {
    isBorrowed = false;
    borrowerId = 0;
}
