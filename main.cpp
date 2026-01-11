#include <iostream>
#include <string> 
#include <limits> // Potrzebne do czyszczenia bufora i numeric_limits
#include <fstream>
#include <map> //do szukania tytułów po autorze

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
    void AuthorSearch(std::string author = "") {
        if (author == "") {
            std::cout << "No author included.\n";
            return;
        }
        
        std::map<std::string, int> book_count;
        std::string line;
        std::ifstream file;
        
        file.open("books.txt", std::ios::in);

        while (std::getline(file, line)) {
            if (line.find(author) != std::string::npos) {
                line.erase(line.find(author));
                book_count[line]++;
            }
        }
        std::cout << "We have " + std::to_string(book_count.size()) + " books made by " + author << std::endl;
        for (auto const& [title, count] : book_count) {
            std::cout << "- " << title << "(" << count << " copies)\n";
        }
        
        file.close();
    }

    void TitleSearch(std::string title = "") {
        if (title == "") {
            std::cout << "No title included.\n";
            return;
        }
        int book_count = 0;
        std::string line;
        std::ifstream file;
        
        file.open("books.txt", std::ios::in);
        
        while (std::getline(file, line)) {
            if (line.find(title) != std::string::npos) 
                book_count++;
        }
        file.close();
        
        std::cout << "We have " + std::to_string(book_count) + " copies of " + title << std::endl;
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
    int role = 0;

    std::cout << "\n-------------------------------LIBRARY SYSTEM-------------------------------\n";
    std::cout << "Select Role:\n";
    std::cout << "1. Administrator\n";
    std::cout << "2. Student\n";
    std::cout << "Choice: ";

    while(!(std::cin >> role) || (role != 1 && role != 2)) {
        std::cout << "Invalid role! Select 1 or 2: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    while(running) {
        std::cout << "\n-------------------------------LIBRARY SYSTEM-------------------------------\n";
        if(role == 1) {
            std::cout << "LOGGED AS: ADMIN\n";
            std::cout << "1. Add Book\n";
            std::cout << "2. Add Student\n";
            std::cout << "3. Search By Author\n";
            std::cout << "4. Search By Title\n";
            std::cout << "5. Exit\n";
        } else {
            std::cout << "LOGGED AS: STUDENT\n";
            std::cout << "1. Borrow Book (Assign book to student)\n"; 
            std::cout << "2. Check Student Balance\n";               
            std::cout << "3. Search By Author\n";
            std::cout << "4. Search By Title\n";
            std::cout << "5. Exit\n";
        }
        std::cout << "Choose option: ";
        
        if(!(std::cin >> choice)) {
            std::cout << "Please enter a number!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if(role == 1) {
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

                        std::ofstream file;
                        file.open("books.txt", std::ios::app);
                        if(file.is_open()) {
                            file << title << ";" << author << ";" << isbn << ";" << yearOfPublishing << "\n";
                            file.close();
                            std::cout << "Book saved to database (books.txt)!\n";
                        }
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

                case 3: { 
                    std::string authorSearch;
                    std::cout << "Enter author to search: ";
                    std::cin.ignore(); 
                    std::getline(std::cin, authorSearch);
                    
                    Student tempSearcher; 
                    tempSearcher.AuthorSearch(authorSearch);
                    break;
                }
                case 4: { 
                    std::string titleSearch;
                    std::cout << "Enter title to search: ";
                    std::cin.ignore();
                    std::getline(std::cin, titleSearch);
                    
                    Student tempSearcher;
                    tempSearcher.TitleSearch(titleSearch);
                    break;
                }
                
                case 5: 
                    running = false;
                    break;
                
                default: std::cout << "Invalid option!\n";
            }
        } else {
            switch(choice) {
                case 1: {
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
                    break;        
                }
                case 2: {
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
                    break; 
                }

                case 3: { 
                    std::string authorSearch;
                    std::cout << "Enter author to search: ";
                    std::cin.ignore(); 
                    std::getline(std::cin, authorSearch);
                    
                    Student tempSearcher;
                    tempSearcher.AuthorSearch(authorSearch);
                    break;
                }
                case 4: { 
                    std::string titleSearch;
                    std::cout << "Enter title to search: ";
                    std::cin.ignore();
                    std::getline(std::cin, titleSearch);
                    
                    Student tempSearcher;
                    tempSearcher.TitleSearch(titleSearch);
                    break;
                }

                case 5:
                    running = false;
                    break;

                default:
                    std::cout << "Invalid option!\n";
            }
        }
    }
    return 0;
}