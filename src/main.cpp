#include <iostream>
#include "Library.hpp"

int main() {
    Library lib;
    lib.loadData();

    std::cout << "=== SYSTEM BIBLIOTECZNY ===\n";

    int choice;
    do {
        std::cout << "\n1. Dodaj książkę"
                  << "\n2. Dodaj studenta"
                  << "\n3. Wypożycz książkę"
                  << "\n4. Zwróć książkę"
                  << "\n5. Pokaż raport"
                  << "\n6. Zapisz i wyjdź"
                  << "\nWybór: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string title, author;
                int isbn, year;
                std::cout << "Tytuł: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Autor: ";
                std::getline(std::cin, author);
                std::cout << "ISBN (liczba): ";
                std::cin >> isbn;
                std::cout << "Rok wydania: ";
                std::cin >> year;

                lib.books[lib.bookCount++] = Book(title, author, isbn, year);
                std::cout << "[OK] Dodano książkę.\n";
                break;
            }

            case 2: {
                std::string first, last, address;
                int id;
                std::cout << "Imię: ";
                std::cin.ignore();
                std::getline(std::cin, first);
                std::cout << "Nazwisko: ";
                std::getline(std::cin, last);
                std::cout << "Adres: ";
                std::getline(std::cin, address);
                std::cout << "ID studenta: ";
                std::cin >> id;

                lib.students[lib.studentCount++] = Student(first, last, id, address);
                std::cout << "[OK] Dodano studenta.\n";
                break;
            }

            case 3: {
                int isbn, studentId;
                std::cout << "ISBN książki: ";
                std::cin >> isbn;
                std::cout << "ID studenta: ";
                std::cin >> studentId;

                bool foundBook = false, foundStudent = false;
                for (int i = 0; i < lib.bookCount; i++) {
                    if (lib.books[i].isbn == isbn && !lib.books[i].isBorrowed) {
                        for (int j = 0; j < lib.studentCount; j++) {
                            if (lib.students[j].id == studentId) {
                                if (lib.students[j].borrowBook(isbn)) {
                                    lib.books[i].borrow();
                                    lib.books[i].borrowerId = studentId;
                                    std::cout << "[OK] Książka wypożyczona.\n";
                                } else {
                                    std::cout << "[BŁĄD] Student osiągnął limit 3 książek.\n";
                                }
                                foundStudent = true;
                                break;
                            }
                        }
                        foundBook = true;
                        break;
                    }
                }
                if (!foundBook) std::cout << "[BŁĄD] Nie znaleziono dostępnej książki.\n";
                if (!foundStudent) std::cout << "[BŁĄD] Nie znaleziono studenta.\n";
                break;
            }

            case 4: {
                int isbn, studentId;
                std::cout << "ISBN książki: ";
                std::cin >> isbn;
                std::cout << "ID studenta: ";
                std::cin >> studentId;

                bool success = false;
                for (int i = 0; i < lib.bookCount; i++) {
                    if (lib.books[i].isbn == isbn && lib.books[i].borrowerId == studentId) {
                        for (int j = 0; j < lib.studentCount; j++) {
                            if (lib.students[j].id == studentId) {
                                if (lib.students[j].returnBook(isbn)) {
                                    lib.books[i].returnBook();
                                    std::cout << "[OK] Książka zwrócona.\n";
                                    success = true;
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
                if (!success) std::cout << "[BŁĄD] Nie znaleziono wypożyczenia.\n";
                break;
            }

            case 5:
                lib.generateReport();
                break;

            case 6:
                lib.saveData();
                std::cout << "[INFO] Dane zapisane. Do zobaczenia!\n";
                break;

            default:
                std::cout << "[!] Nieprawidłowy wybór.\n";
        }

    } while (choice != 6);

    return 0;
}
