#include <iostream>
#include <string>
#include "../include/Library.hpp"

int main() {
    Library lib;        //tworzenie obiekt. klasy
    lib.loadData();

    std::cout << "--- LIBRARY SYSTEM ---\n";
    int mode;
    std::cout << "1. Administrator\n2. Student\nChoose mode: ";
    std::cin >> mode;

    if (mode == 1) {

        int choice;
        do {
            std::cout << "\n--- ADMIN MENU ---\n";
            std::cout << "1. Add Book\n2. Add Student\n3. Generate Report\n4. Exit\nChoice: ";
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
                    
                    bool isUnique = false;
                    do {
                        std::cout << "Student ID: ";
                        std::cin >> id;
                        
                        isUnique = true; 
                        for(int i = 0; i < lib.studentCount; i++) {
                            if(lib.students[i].id == id) {
                                std::cout << "[ERROR] ID " << id << " already exists! Try another.\n";
                                isUnique = false;
                                break;
                            }
                        }
                    } while (!isUnique);

                    lib.students[lib.studentCount++] = Student(first, last, id, address);
                    std::cout << "[OK] Student added.\n";
                    break;
                }
                case 3:
                    lib.generateReport();
                    break;
                case 4:
                    lib.saveData();
                    std::cout << "[INFO] Data saved. Goodbye!\n";
                    break;
                default:
                    std::cout << "[!] Incorrect selection.\n";
            }
        } while (choice != 4);
    }
    else if (mode == 2) {
                                    //  STUDENT LOGIN
        int studentIndex = -1;
        while (studentIndex == -1) {
            std::cout << "\n1. Log in\n2. Create library account\nChoice: ";
            int loginChoice;
            std::cin >> loginChoice;

            if (loginChoice == 1) {
                int studentId;
                std::cout << "Enter your student ID: ";
                std::cin >> studentId;
                for (int i = 0; i < lib.studentCount; i++) {
                    if (lib.students[i].id == studentId) {
                        studentIndex = i;
                        break;
                    }
                }
                if (studentIndex == -1) {
                    std::cout << "[ERROR] No account found. Try again.\n";
                } else {
                    std::cout << "[OK] Welcome, " << lib.students[studentIndex].firstName << "!\n";
                }
            } else if (loginChoice == 2) {
                std::string first, last, address;
                std::cout << "Name: "; std::cin.ignore(); std::getline(std::cin, first);
                std::cout << "Surname: "; std::getline(std::cin, last);
                std::cout << "Address: "; std::getline(std::cin, address);
                
                int newId = 1000 + lib.studentCount;
                bool idExists = true;

                while (idExists) {
                    idExists = false;
                    for(int i = 0; i < lib.studentCount; i++) {
                        if (lib.students[i].id == newId) {
                            newId++;     
                            idExists = true; 
                            break;
                        }
                    }
                }

                lib.students[lib.studentCount++] = Student(first, last, newId, address);
                studentIndex = lib.studentCount - 1;
                std::cout << "[OK] Account created! Your ID: " << newId << "\n";
            } else {
                return 0;
            }
        }


        int choice;
        do {
            std::cout << "\n--- STUDENT MENU ---\n";
            std::cout << "1. Borrow a Book\n2. Return Book\n3. Check My Account\n4. Search (Author)\n5. Search (Title)\n6. Exit\nChoice: ";
            std::cin >> choice;

            switch (choice) {
                case 1: { 
                    int isbn;
                    std::cout << "ISBN: "; std::cin >> isbn;
                    bool found = false;
                    for (int i = 0; i < lib.bookCount; i++) {
                        if (lib.books[i].isbn == isbn && !lib.books[i].isBorrowed) {
                            if (lib.students[studentIndex].borrowBook(isbn)) {
                                lib.books[i].borrow();
                                lib.books[i].borrowerId = lib.students[studentIndex].id;
                                std::cout << "[OK] Book borrowed.\n";
                            } else std::cout << "[ERROR] Limit reached.\n";
                            found = true; break;
                        }
                    }
                    if (!found) std::cout << "[ERROR] Book unavailable.\n";
                    break;
                }
                case 2: { 
                    int isbn;
                    std::cout << "ISBN to return: "; std::cin >> isbn;
                    if (lib.students[studentIndex].returnBook(isbn)) {
                        for (int i = 0; i < lib.bookCount; i++) {
                            if (lib.books[i].isbn == isbn) {
                                lib.books[i].returnBook();
                                break;
                            }
                        }
                        std::cout << "[OK] Returned.\n";
                    } else std::cout << "[ERROR] You don't have this book.\n";
                    break;
                }
                case 3: { 
                    Person* personPtr = &lib.students[studentIndex];
                    std::cout << "\n--- Account Details ---\n";
                    personPtr->introduce();
                    lib.students[studentIndex].showAccount();
                    break;
                }
                case 4: { 
                    std::string a;
                    std::cout << "Enter author: "; std::cin.ignore(); std::getline(std::cin, a);
                    for (int i = 0; i < lib.bookCount; i++) {
                        if (lib.books[i].author.find(a) != std::string::npos) 
                            std::cout << "- " << lib.books[i].title << " (ISBN: " << lib.books[i].isbn << ")\n";
                    }
                    break;
                }
                case 5: { 
                    std::string t;
                    std::cout << "Enter title: "; std::cin.ignore(); std::getline(std::cin, t);
                    for (int i = 0; i < lib.bookCount; i++) {
                        if (lib.books[i].title.find(t) != std::string::npos) 
                             std::cout << "- " << lib.books[i].title << " (" << lib.books[i].author << ")\n";
                    }
                    break;
                }
                case 6:
                    lib.saveData();
                    std::cout << "[INFO] Goodbye!\n";
                    break;
                default:
                    std::cout << "[!] Invalid choice.\n";
            }
        } while (choice != 6);
    } else {
        std::cout << "[ERROR] Invalid mode!\n";
    }

    return 0;
}