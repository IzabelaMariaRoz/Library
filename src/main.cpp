#include <iostream>
#include "Library.hpp"

int main() {
    Library lib;
    lib.loadData();

    std::cout << "--- LIBRARY SYSTEM ---\n";
    int mode;
    std::cout << "1. Administrator\n2. Student\nChoose mode: ";
    std::cin >> mode;

    int choice;

    if (mode == 1) {
        // =================== ADMIN MENU ===================
        do {
            std::cout << "\n--- ADMIN MENU ---\n";
            std::cout << "1. Add Book\n2. Add Student\n3. Borrow a Book\n4. Return Book\n5. Generate Report\n6. Exit\nChoice: ";
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
                    int isbn, studentId, studentIndex = -1;
                    std::cout << "Student ID: ";
                    std::cin >> studentId;
                    for (int i = 0; i < lib.studentCount; i++) {
                        if (lib.students[i].id == studentId) {
                            studentIndex = i;
                            break;
                        }
                    }
                    if (studentIndex == -1) {
                        std::cout << "[ERROR] Student not found.\n";
                        break;
                    }

                    std::cout << "ISBN of the book: ";
                    std::cin >> isbn;
                    bool foundBook = false;
                    for (int i = 0; i < lib.bookCount; i++) {
                        if (lib.books[i].isbn == isbn && !lib.books[i].isBorrowed) {
                            if (lib.students[studentIndex].borrowBook(isbn)) {
                                lib.books[i].borrow();
                                lib.books[i].borrowerId = lib.students[studentIndex].id;
                                std::cout << "[OK] Book borrowed.\n";
                            } else {
                                std::cout << "[ERROR] Student has reached the limit of 3 books.\n";
                            }
                            foundBook = true;
                            break;
                        }
                    }
                    if (!foundBook) std::cout << "[ERROR] No available book found.\n";
                    break;
                }

                case 4: {
                    int isbn, studentId, studentIndex = -1;
                    std::cout << "Student ID: ";
                    std::cin >> studentId;
                    for (int i = 0; i < lib.studentCount; i++) {
                        if (lib.students[i].id == studentId) {
                            studentIndex = i;
                            break;
                        }
                    }
                    if (studentIndex == -1) {
                        std::cout << "[ERROR] Student not found.\n";
                        break;
                    }

                    std::cout << "ISBN of the book to return: ";
                    std::cin >> isbn;
                    bool returned = lib.students[studentIndex].returnBook(isbn);
                    if (returned) {
                        bool bookFound = false;
                        for (int i = 0; i < lib.bookCount; i++) {
                            if (lib.books[i].isbn == isbn && lib.books[i].borrowerId == lib.students[studentIndex].id) {
                                lib.books[i].returnBook();
                                bookFound = true;
                                break;
                            }
                        }
                        if (bookFound)
                            std::cout << "[OK] Book returned.\n";
                        else
                            std::cout << "[ERROR] Book not found in library records.\n";
                    } else {
                        std::cout << "[ERROR] Student didn’t borrow this book.\n";
                    }
                    break;
                }

                case 5:
                    lib.generateReport();
                    break;

                case 6:
                    lib.saveData();
                    std::cout << "[INFO] Data saved. Goodbye!\n";
                    break;

                default:
                    std::cout << "[!] Incorrect selection.\n";
            }

        } while (choice != 6);
    }

    else if (mode == 2) {
        // =================== STUDENT LOGIN ===================
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
                    std::cout << "[ERROR] No account found for this ID. Try again.\n";
                    continue; // powrót do logowania
                }
                std::cout << "[OK] Welcome, " << lib.students[studentIndex].firstName
                          << " " << lib.students[studentIndex].lastName << "!\n";
            }

            else if (loginChoice == 2) {
                std::string first, last, address;
                std::cout << "Name: ";
                std::cin.ignore();
                std::getline(std::cin, first);
                std::cout << "Surname: ";
                std::getline(std::cin, last);
                std::cout << "Address: ";
                std::getline(std::cin, address);

                int newId = 1000 + lib.studentCount;
                lib.students[lib.studentCount++] = Student(first, last, newId, address);
                studentIndex = lib.studentCount - 1;

                std::cout << "[OK] Account created! Your student ID is: " << newId << "\n";
            }

            else {
                std::cout << "[!] Invalid choice.\n";
                continue;
            }
        }

        // =================== STUDENT MENU ===================
            do {
                std::cout << "\n--- STUDENT MENU ---\n";
                std::cout << "1. Borrow a Book"
                          << "\n2. Return Book"
                          << "\n3. Check My Account"
                          << "\n4. Search (Author)"
                          << "\n5. Search (Title)"
                          << "\n6. Exit"
                          << "\nChoice: ";
                std::cin >> choice;

                switch (choice) {
                    case 1: {
                        int isbn;
                        std::cout << "ISBN of the book: ";
                        std::cin >> isbn;

                        bool foundBook = false;
                        for (int i = 0; i < lib.bookCount; i++) {
                            if (lib.books[i].isbn == isbn && !lib.books[i].isBorrowed) {
                                if (lib.students[studentIndex].borrowBook(isbn)) {
                                    lib.books[i].borrow();
                                    lib.books[i].borrowerId = lib.students[studentIndex].id;
                                    std::cout << "[OK] Book borrowed.\n";
                                } else {
                                    std::cout << "[ERROR] You have reached the limit of 3 books.\n";
                                }
                                foundBook = true;
                                break;
                            }
                        }
                        if (!foundBook) std::cout << "[ERROR] No available book found.\n";
                        break;
                    }

                    case 2: {
                        int isbn;
                        std::cout << "ISBN of the book to return: ";
                        std::cin >> isbn;

                        bool returned = lib.students[studentIndex].returnBook(isbn);
                        if (returned) {
                            for (int i = 0; i < lib.bookCount; i++) {
                                if (lib.books[i].isbn == isbn) {
                                    lib.books[i].returnBook();
                                    break;
                                }
                            }
                            std::cout << "[OK] Book returned.\n";
                        } else {
                            std::cout << "[ERROR] You didn’t borrow this book.\n";
                        }
                        break;
                    }
                    case 3: {
                        int sID; std::cout << "Enter ID: "; cin >> sID;
                        bool found = false;
                        for(int i=0; i<lib.studentCount; i++) {
                            if(lib.students[i].id == sID) {
                                Person* personPtr = &lib.students[i];
                                personPtr->introduce(); 
                                
                                lib.students[i].showAccount();
                                found = true;
                                break;
                            }
                    }
                }
                case 4: {
                    std::string a; 
                    std::cout << "Enter author: "; cin.ignore(); getline(cin, a);
                    for(int i=0; i<lib.bookCount; i++) {
                        if(lib.books[i].author == a) std::cout << "- " << lib.books[i].title << endl;
                    }
                    break;
                }
                case 5: {
                    std::string t;
                    std::cout << "Enter title: "; cin.ignore(); getline(cin, t);
                    for(int i=0; i<lib.bookCount; i++) {
                         if(lib.books[i].title.find(t) != string::npos) 
                            std::cout << "- " << lib.books[i].title << " (" << lib.books[i].author << ")\n";
                    }
                    break;
                }

                    case 6:
                        std::cout << "[INFO] Goodbye!\n";
                        break;

                    default:
                        std::cout << "[!] Incorrect selection.\n";
                }
                if(!found) std::cout << "Student not found.\n";
                    break;

            } while (choice != 6);

            lib.saveData();
            break; // po zakończeniu studenta wyjście z pętli
        }

        else {
            std::cout << "[ERROR] Invalid mode selected!\n";
            break;
        }

    return 0;
}
