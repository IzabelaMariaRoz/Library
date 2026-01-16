#include "Student.hpp"

Student::Student() {
    borrowedCount = 0;
    for (int i = 0; i < 3; i++) borrowedISBNs[i] = 0;
}

Student::Student(const std::string& f, const std::string& l, int id, const std::string& address)
    : Person(f, l), id(id), address(address), borrowedCount(0)
{
    for (int i = 0; i < 3; i++) borrowedISBNs[i] = 0;
}

void Student::introduce() {
    std::cout << "I am a student: " << firstName << " " << lastName
              << " (ID: " << id << ")" << std::endl;
}

bool Student::borrowBook(int isbn) {
    if (borrowedCount < 3) {
        borrowedISBNs[borrowedCount++] = isbn;
        return true;
    }
    return false;
}

bool Student::returnBook(int isbn) {
    for (int i = 0; i < borrowedCount; i++) {
        if (borrowedISBNs[i] == isbn) {
            for (int j = i; j < borrowedCount - 1; j++)
                borrowedISBNs[j] = borrowedISBNs[j + 1];
            borrowedISBNs[borrowedCount - 1] = 0;
            borrowedCount--;
            return true;
        }
    }
    return false;
}

void Student::showAccount() {
    introduce();
    std::cout << "Books borrowed: " << borrowedCount << "/3" << std::endl;
    if (borrowedCount > 0) {
        std::cout << "Borrowed ISBNs: ";
        for (int i = 0; i < borrowedCount; i++)
            std::cout << borrowedISBNs[i] << " ";
        std::cout << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
}
