#include <iostream>
#include <string>
#include <fstream>
#include <limits> // czyśczenie buforu

using namespace std;

class Person {
public:
    string firstName;
    string lastName;

    Person() {}
    Person(string f, string l) {
        firstName = f;
        lastName = l;
    }

    virtual void introduce() = 0;
};

class Book {
public:
    class Date {
    public:
        int year;
        Date() { year = 0; }
        Date(int y) { year = y; }
    };

    string title;
    string author;
    int isbn;
    Date publishDate; 
    bool isBorrowed;
    int borrowerId;   

    Book() {
        isbn = 0;
        isBorrowed = false;
        borrowerId = 0;
    }

    Book(string t, string a, int i, int y) {
        title = t;
        author = a;
        isbn = i;
        publishDate = Date(y);
        isBorrowed = false;
        borrowerId = 0;
    }
};

class Student : public Person {
public:
    int id;
    string address;
    int borrowedISBNs[3]; 
    int borrowedCount;

    Student() {
        borrowedCount = 0;
        for(int i=0; i<3; i++) borrowedISBNs[i] = 0;
    }

    Student(string f, string l, int id, string a) : Person(f, l) {
        this->id = id;
        this->address = a;
        this->borrowedCount = 0;
        for(int k=0; k<3; k++) borrowedISBNs[k] = 0;
    }

    void introduce() override {
        cout << "I am a student: " << firstName << " " << lastName << " (ID: " << id << ")" << endl;
    }

    bool borrowBook(int isbn) {
        if (borrowedCount < 3) {
            borrowedISBNs[borrowedCount] = isbn;
            borrowedCount++;
            return true;
        }
        return false;
    }
    
    void showAccount() {
        introduce(); 
        cout << "Books borrowed: " << borrowedCount << "/3" << endl;
        if (borrowedCount > 0) {
            cout << "Borrowed ISBNs: ";
            for(int i=0; i<borrowedCount; i++) {
                cout << borrowedISBNs[i] << " ";
            }
            cout << endl;
        }
        cout << "-----------------------" << endl;
    }

    bool returnBook(int isbn) {
    for (int i = 0; i < borrowedCount; i++) {
        if (borrowedISBNs[i] == isbn) {
            for (int j = i; j < borrowedCount - 1; j++) {
                borrowedISBNs[j] = borrowedISBNs[j+1];
            }
            borrowedISBNs[borrowedCount - 1] = 0;
            borrowedCount--;
            return true;
        }
    }
    return false;
}
};

const int MAX_STUDENTS = 100;
const int MAX_BOOKS = 100;

Student students[MAX_STUDENTS];
Book library[MAX_BOOKS];

int studentCount = 0;
int bookCount = 0;


void saveData() {
    ofstream bookFile("books.txt");
        if (bookFile.is_open()) {
            for (int i = 0; i < bookCount; i++) {
                bookFile << library[i].isbn << ";"
                        << library[i].title << ";"
                        << library[i].author << ";"
                        << library[i].publishDate.year << ";"
                        << library[i].isBorrowed << ";"
                        << library[i].borrowerId << endl;
            }
            bookFile.close();
        }

    ofstream studentFile("students.txt");
        if (studentFile.is_open()) {
            for (int i = 0; i < studentCount; i++) {
                studentFile << students[i].id << ";"
                            << students[i].firstName << ";"
                            << students[i].lastName << ";"
                            << students[i].address << ";"
                            << students[i].borrowedCount << ";";
                
                for(int j=0; j<3; j++) {
                    studentFile << students[i].borrowedISBNs[j];
                    if(j < 2) studentFile << ";"; 
                }
                studentFile << endl;
            }
            studentFile.close();
        }
    cout << "[INFO] Data saved to files." << endl;
}

void loadData() {
ifstream bookFile("books.txt");
    bookCount = 0;
    if (bookFile.is_open()) {
        while (bookCount < MAX_BOOKS && bookFile >> library[bookCount].isbn) {
            bookFile.ignore(); 
            getline(bookFile, library[bookCount].title, ';');
            getline(bookFile, library[bookCount].author, ';');
            bookFile >> library[bookCount].publishDate.year;
            bookFile.ignore(); 
            bookFile >> library[bookCount].isBorrowed;
            bookFile.ignore(); 
            bookFile >> library[bookCount].borrowerId;
            bookFile.ignore(); 
            bookCount++; 
        }
        bookFile.close();
    }

    ifstream studentFile("students.txt");
        studentCount = 0;
        if (studentFile.is_open()) {
            while (studentCount < MAX_STUDENTS && studentFile >> students[studentCount].id) {
                studentFile.ignore();
                getline(studentFile, students[studentCount].firstName, ';');
                getline(studentFile, students[studentCount].lastName, ';');
                getline(studentFile, students[studentCount].address, ';');
                studentFile >> students[studentCount].borrowedCount;
                studentFile.ignore(); 
                for(int j=0; j<3; j++) {
                    studentFile >> students[studentCount].borrowedISBNs[j];
                    studentFile.ignore(); 
                }
                studentCount++;
            }
            studentFile.close();
        }
}

void generateReport() {
    ofstream report("report.txt");
    report << "LIBRARY REPORT" << endl;
    report << "Total Books: " << bookCount << endl;
    report << "Total Students: " << studentCount << endl;
    report << "--------------------------------" << endl;
    report << "BORROWED BOOKS:" << endl;
    
    bool anyBorrowed = false;
    for(int i=0; i<bookCount; i++) {
        if(library[i].isBorrowed) {
            report << "- " << library[i].title << " (ISBN: " << library[i].isbn << ") -> Student ID: " << library[i].borrowerId << endl;
            anyBorrowed = true;
        }
    }
    if(!anyBorrowed) report << "No books currently borrowed." << endl;
    
    report.close();
    cout << "[INFO] Report generated (report.txt)." << endl;
}

int main() {
    loadData();

    bool running = true;
    int role = 0;
    int choice;

    cout << "\n--- LIBRARY SYSTEM ---" << endl;
    cout << "1. Administrator" << endl;
    cout << "2. Student" << endl;
    cout << "Select role: ";
    
    while(!(cin >> role) || (role != 1 && role != 2)) {
        cout << "Invalid role! Select 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while(running) {
        cout << "\n--- MENU ---" << endl;
        if(role == 1) { 
            cout << "1. Add Book" << endl;
            cout << "2. Add Student" << endl;
            cout << "3. Search (Author)" << endl;
            cout << "4. Generate Report" << endl;
            cout << "5. Exit" << endl;
        } else { 
            cout << "1. Borrow Book" << endl;
            cout << "2. Check My Account" << endl;
            cout << "3. Search (Author)" << endl;
            cout << "4. Search (Title)" << endl;
            cout << "5. Return Book" << endl;
            cout << "6. Exit" << endl;
        }
        cout << "Choice: ";
        cin >> choice;

        if(role == 1) { 
            switch(choice) {
                case 1: {
                    if (bookCount < MAX_BOOKS) {
                        string t, a; int isbn, y;
                        cin.ignore();
                        cout << "Title: "; getline(cin, t);
                        cout << "Author: "; getline(cin, a);
                        cout << "ISBN: "; cin >> isbn;
                        cout << "Year: "; cin >> y;
                        
                        library[bookCount] = Book(t, a, isbn, y);
                        bookCount++;
                        saveData();
                    } else cout << "Database full!\n";
                    break;
                }
                case 2: {
                    if (studentCount < MAX_STUDENTS) {
                        string fn, ln, ad; int id;
                        cout << "First Name: "; cin >> fn;
                        cout << "Last Name: "; cin >> ln;
                        cout << "ID: "; cin >> id;
                        cin.ignore();
                        cout << "Address: "; getline(cin, ad);

                        students[studentCount] = Student(fn, ln, id, ad);
                        studentCount++;
                        saveData();
                    } else cout << "Student list full!\n";
                    break;
                }
                case 3: {
                     string a; 
                     cout << "Enter author: "; cin.ignore(); getline(cin, a);
                     for(int i=0; i<bookCount; i++) {
                         if(library[i].author == a) cout << "- " << library[i].title << endl;
                     }
                     break;
                }
                case 4:
                    generateReport();
                    break;
                case 5:
                    running = false;
                    break;
                default:
                    cout << "Invalid option!\n";
            }
        } else { 
            switch(choice) {
                case 1: {
                    int sID, bISBN;
                    cout << "Enter your ID: "; cin >> sID;
                    
                    int studentIndex = -1;
                    for(int i=0; i<studentCount; i++) {
                        if(students[i].id == sID) { studentIndex = i; break; }
                    }

                    if(studentIndex != -1) {
                        cout << "Enter Book ISBN: "; cin >> bISBN;
                        int bookIndex = -1;
                        for(int i=0; i<bookCount; i++) {
                            if(library[i].isbn == bISBN) { bookIndex = i; break; }
                        }

                        if(bookIndex != -1) {
                            if(!library[bookIndex].isBorrowed) {
                                if(students[studentIndex].borrowBook(bISBN)) {
                                    library[bookIndex].isBorrowed = true;
                                    library[bookIndex].borrowerId = sID;
                                    cout << "Success! Book borrowed.\n";
                                    saveData();
                                } else cout << "Limit reached (3 books)!\n";
                            } else cout << "Book already borrowed!\n";
                        } else cout << "Book with this ISBN not found.\n";
                    } else cout << "Student not found.\n";
                    break;
                }
                case 2: {
                    int sID; cout << "Enter ID: "; cin >> sID;
                    bool found = false;
                    for(int i=0; i<studentCount; i++) {
                        if(students[i].id == sID) {
                            Person* personPtr = &students[i];
                            personPtr->introduce(); 
                            
                            students[i].showAccount();
                            found = true;
                            break;
                        }
                    }
                    if(!found) cout << "Student not found.\n";
                    break;
                }
                case 3: {
                    string a; 
                    cout << "Enter author: "; cin.ignore(); getline(cin, a);
                    for(int i=0; i<bookCount; i++) {
                        if(library[i].author == a) cout << "- " << library[i].title << endl;
                    }
                    break;
                }
                case 4: {
                    string t;
                    cout << "Enter title: "; cin.ignore(); getline(cin, t);
                    for(int i=0; i<bookCount; i++) {
                         if(library[i].title.find(t) != string::npos) 
                            cout << "- " << library[i].title << " (" << library[i].author << ")\n";
                    }
                    break;
                }
                case 5: {
                    int sID, bISBN;
                    cout << "Enter your ID: "; cin >> sID;

                    int studentIndex = -1;
                    for(int i=0; i<studentCount; i++) {
                        if(students[i].id == sID) { studentIndex = i; break; }
                    }

                    if (studentIndex != -1) {
                        cout << "Enter Book ISBN to return: "; cin >> bISBN;
                        int bookIndex = -1;
                        for(int i=0; i<bookCount; i++) {
                            if(library[i].isbn == bISBN) { bookIndex = i; break; }
                        }

                        if (bookIndex != -1) {
                            if (students[studentIndex].returnBook(bISBN)) {
                                library[bookIndex].isBorrowed = false;
                                library[bookIndex].borrowerId = 0;
                                
                                cout << "Success! Book returned.\n";
                                saveData(); 
                            } else {
                                cout << "You generally don't have this book borrowed in your account.\n";
                            }
                        } else {
                            cout << "Book with this ISBN does not exist in the library database.\n";
                        }
                    } else {
                        cout << "Student not found.\n";
                    }
                    break;
                }
                case 6:
                    running = false;
                    break;
                default:
                    cout << "Invalid option!\n";
            }
        }
    }
    return 0;
}