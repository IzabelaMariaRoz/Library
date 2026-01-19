#include <iostream>
#include "Library.hpp"

int main() {
    Library lib;
    lib.loadData();

    std::cout << "--- LIBRARY SYSTEM ---\n";

    int choice;
    do {
        std::cout << "\n1. Add Book"
                  << "\n2. Add Student"
                  << "\n3. Borrow a book"
                  << "\n4. Return Book"
                  << "\n5. Generate Report"
                  << "\n6. Exit"
                  << "\nChoice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string title, author;
                int isbn, year;
                std::cout << "Title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Author: ";
                std::getline(std::cin, author);
                std::cout << "ISBN: ";
                std::cin >> isbn;
                std::cout << "Year: ";
                std::cin >> year;

                lib.books[lib.bookCount++] = Book(title, author, isbn, year);
                std::cout << "[OK] Book added.\n";
                break;
            }

            case 2: {
                std::string first, last, address;
                int id;
                std::cout << "Name: ";
                std::cin.ignore();
                std::getline(std::cin, first);
                std::cout << "Surname: ";
                std::getline(std::cin, last);
                std::cout << "Address: ";
                std::getline(std::cin, address);
                std::cout << "Student ID: ";
                std::cin >> id;

                lib.students[lib.studentCount++] = Student(first, last, id, address);
                std::cout << "[OK] Student added.\n";
                break;
            }

            case 3: {
                int isbn, studentId;
                std::cout << "ISBN of the book: ";
                std::cin >> isbn;
                std::cout << "Student ID:  ";
                std::cin >> studentId;

                bool foundBook = false, foundStudent = false;
                for (int i = 0; i < lib.bookCount; i++) {
                    if (lib.books[i].isbn == isbn && !lib.books[i].isBorrowed) {
                        for (int j = 0; j < lib.studentCount; j++) {
                            if (lib.students[j].id == studentId) {
                                if (lib.students[j].borrowBook(isbn)) {
                                    lib.books[i].borrow();
                                    lib.books[i].borrowerId = studentId;
                                    std::cout << "[OK] Book borrowed.\n";
                                } else {
                                    std::cout << "[ERROR] Student has reached the limit of 3 books.\n";
                                }
                                foundStudent = true;
                                break;
                            }
                        }
                        foundBook = true;
                        break;
                    }
                }
                if (!foundBook) std::cout << "[ERROR] No available book found.\n";
                if (!foundStudent) std::cout << "[ERROR] Student not found.\n";
                break;
            }

            case 4: {
                int isbn, studentId;
                std::cout << "ISBN of the book: ";
                std::cin >> isbn;
                std::cout << "Student ID: ";
                std::cin >> studentId;

                bool success = false;
                for (int i = 0; i < lib.bookCount; i++) {
                    if (lib.books[i].isbn == isbn && lib.books[i].borrowerId == studentId) {
                        for (int j = 0; j < lib.studentCount; j++) {
                            if (lib.students[j].id == studentId) {
                                if (lib.students[j].returnBook(isbn)) {
                                    lib.books[i].returnBook();
                                    std::cout << "[OK] Book returned.\n";
                                    success = true;
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
                if (!success) std::cout << "[ERROR] No rental found.\n";
                break;
            }

            case 5:
                lib.generateReport();
                break;

            case 6:
                lib.saveData();
                std::cout << "[INFO] Data saved. See you soon!\n";
                break;

            default:
                std::cout << "[!] Incorrect selection.\n";
        }

    } while (choice != 6);

    return 0;
}
