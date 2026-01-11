#include "Library.hpp"
#include <iostream>

int main() {
    Library library;
    library.loadBooks("data/books.txt");
    library.loadStudents("data/students.txt");

    bool running = true;
    int choice;

    while(running) {
        std::cout << "\n--- Library Menu ---\n";
        std::cout << "1. Add Book\n2. Add Student\n3. Borrow Book\n4. Check Student Balance\n5. Exit\n";
        std::cout << "Choose option: ";
        std::cin >> choice;

        switch(choice) {
            case 1: {
                std::string title, author;
                int isbn, year;
                std::cin.ignore();
                std::cout << "Title: "; std::getline(std::cin, title);
                std::cout << "Author: "; std::getline(std::cin, author);
                std::cout << "ISBN: "; std::cin >> isbn;
                std::cout << "Year: "; std::cin >> year;
                library.addBook(Book(title, author, isbn, year));
                break;
            }
            case 2: {
                std::string name, lastName, address;
                int id;
                std::cout << "Name: "; std::cin >> name;
                std::cout << "Last Name: "; std::cin >> lastName;
                std::cout << "ID: "; std::cin >> id;
                std::cin.ignore();
                std::cout << "Address: "; std::getline(std::cin, address);
                library.addStudent(Student(name, lastName, id, address));
                break;
            }
            case 3: {
                int studentID, bookISBN;
                std::cout << "Student ID: "; std::cin >> studentID;
                std::cout << "Book ISBN: "; std::cin >> bookISBN;
                if(library.borrowBook(studentID, bookISBN)) {
                    std::cout << "Book borrowed successfully!\n";
                } else {
                    std::cout << "Cannot borrow this book.\n";
                }
                break;
            }
            case 4: {
                int studentID;
                std::cout << "Student ID: "; std::cin >> studentID;
                library.checkStudentBalance(studentID);
                break;
            }
            case 5:
                running = false;
                break;
            default:
                std::cout << "Invalid option!\n";
        }
    }

    library.saveBooks("data/books.txt");
    library.saveStudents("data/students.txt");

    return 0;
}
