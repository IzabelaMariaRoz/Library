#include <iostream>
#include <string> 
#include <limits> // Potrzebne do czyszczenia bufora i numeric_limits
#include <fstream>

class Book {
public:
    std::string title;
    std::string author;
    int isbn;
    int yearOfPublishing;

    Book() {}

    Book(std::string title, std::string author, int isbn, int yearOfPublishing) {
        this->title = title;
        this->author = author;
        this->isbn = isbn;
        this->yearOfPublishing = yearOfPublishing;
    }
};

class Student {
public: 
    std::string name;
    std::string lastName;
    int id;
    std::string address;
    
    int borrowedBookISBNs[3]; 
    int borrowedCount;

    Student() {
        borrowedCount = 0;
        for(int i=0; i<3; i++) borrowedBookISBNs[i] = 0;
    }

    Student(std::string name, std::string lastName, int id, std::string address) {
        this->name = name;
        this->lastName = lastName;
        this->id = id;
        this->address = address;
        
        this->borrowedCount = 0;
        for(int i=0; i<3; i++) borrowedBookISBNs[i] = 0;
    }

    bool borrowBook(int isbn) {
        if (borrowedCount < 3) {
            borrowedBookISBNs[borrowedCount] = isbn;
            borrowedCount++;
            return true;
        } else {
            return false; 
        }
    }

    void checkBalance() {
        std::cout << "--- Student Balance ---\n";
        std::cout << "Student: " << name << " " << lastName << " (ID: " << id << ")\n";
        std::cout << "Books borrowed: " << borrowedCount << "/3\n";
        if (borrowedCount > 0) {
            std::cout << "Borrowed ISBNs: ";
            for(int i = 0; i < borrowedCount; i++) {
                std::cout << borrowedBookISBNs[i] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "-----------------------\n";
    }
};


int main() {
    const int MAX_STUDENTS = 7; 
    const int MAX_BOOKS = 10;

    Student students[MAX_STUDENTS]; 
    Book library[MAX_BOOKS];

    int studentCount = 0;
    int bookCount = 0;

    // Menu
    bool running = true;
    int choice;

    while(running) {
        std::cout << "\n-------------------------------LIBRARY SYSTEM-------------------------------\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Add Student\n";
        std::cout << "3. Borrow Book (Assign book to student)\n"; 
        std::cout << "4. Check Student Balance\n";               
        std::cout << "5. Exit\n";
        std::cout << "Choose option: ";
        
        if(!(std::cin >> choice)) {
            std::cout << "Please enter a number!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch(choice) {
            case 1:
                if (bookCount < MAX_BOOKS) {
                    std::string title, author;
                    int isbn, yearOfPublishing;

                    std::cin.ignore();

                    std::cout << "Enter title: ";
                    std::getline(std::cin, title);
                    std::cout << "Enter author: ";
                    std::getline(std::cin, author);
                    std::cout << "Enter ISBN: ";
                    std::cin >> isbn;
                    std::cout << "Enter year of publishing: ";
                    std::cin >> yearOfPublishing;

                    library[bookCount] = Book(title, author, isbn, yearOfPublishing);
                    bookCount++;
                    std::cout << "Book added successfully!\n";

                } else {
                    std::cout << "Library is full!\n";
                }
                break;

            case 2:
                if (studentCount < MAX_STUDENTS) {
                    std::string n, l, a;
                    int i;

                    std::cout << "Enter Name: ";
                    std::cin >> n;
                    std::cout << "Enter Last Name: ";
                    std::cin >> l;
                    std::cout << "Enter ID: ";
                    std::cin >> i;

                    std::cin.ignore();
                    std::cout << "Enter Address: ";
                    std::getline(std::cin, a);

                    students[studentCount] = Student(n, l, i, a);
                    studentCount++;
                    
                    std::cout << "Student added successfully!\n";
                } else {
                    std::cout << "Student list is full! Cannot add more.\n";
                }
                break;

            case 3:
                {
                    int sID, bISBN;
                    bool studentFound = false;
                    bool bookFound = false;
                    int studentIndex = -1;

                    std::cout << "Enter Student ID: ";
                    std::cin >> sID;

                    for(int k=0; k < studentCount; k++) {
                        if(students[k].id == sID) {
                            studentFound = true;
                            studentIndex = k;
                            break;
                        }
                    }

                    if(!studentFound) {
                        std::cout << "Student not found!\n";
                        break;
                    }

                    std::cout << "Enter Book ISBN to borrow: ";
                    std::cin >> bISBN;

                    // (Opcjonalnie) Sprawdzenie czy książka istnieje w bibliotece
                    for(int k=0; k < bookCount; k++) {
                        if(library[k].isbn == bISBN) {
                            bookFound = true;
                            break;
                        }
                    }

                    if(bookFound) {
                        if(students[studentIndex].borrowBook(bISBN)) {
                            std::cout << "Book borrowed successfully!\n";
                        } else {
                            std::cout << "Student has reached the limit of borrowed books (3)!\n";
                        }
                    } else {
                        std::cout << "Book with this ISBN does not exist in the library.\n";
                    }
                }
                break;

            case 4:
                {
                    int sID;
                    bool found = false;
                    std::cout << "Enter Student ID to check: ";
                    std::cin >> sID;

                    for(int k=0; k < studentCount; k++) {
                        if(students[k].id == sID) {
                            students[k].checkBalance();
                            found = true;
                            break;
                        }
                    }
                    if(!found) std::cout << "Student not found.\n";
                }
                break;

            case 5:
                running = false;
                break;

            default:
                std::cout << "Invalid option!\n";
        }
    }
    return 0;
}
