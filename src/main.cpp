#include "Library.hpp"
#include <iostream>
#include <limits>

int main() {
    Library library;
    library.loadData();

    bool running = true;
    int role = 0;

    std::cout << "\n--- LIBRARY SYSTEM ---\n";
    std::cout << "1. Administrator\n2. Student\nSelect role: ";
    while (!(std::cin >> role) || (role != 1 && role != 2)) {
        std::cout << "Invalid role! Select 1 or 2: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int choice;
    while(running) {
        std::cout << "\n--- MENU ---\n";
        if(role==1)
            std::cout << "1. Add Book\n2. Add Student\n3. Search by Author\n4. Generate Report\n5. Exit\n";
        else
            std::cout << "1. Borrow Book\n2. Check Account\n3. Search by Author\n4. Search by Title\n5. Return Book\n6. Exit\n";

        std::cout << "Choice: ";
        std::cin >> choice;

        if(role==1) {
            switch(choice) {
                case 1: {
                    if(library.bookCount >= Library::MAX_BOOKS) { std::cout << "Book database full!\n"; break; }
                    std::string t,a; int isbn,y;
                    std::cin.ignore();
                    std::cout << "Title: "; std::getline(std::cin,t);
                    std::cout << "Author: "; std::getline(std::cin,a);
                    std::cout << "ISBN: "; std::cin >> isbn;
                    std::cout << "Year: "; std::cin >> y;
                    library.books[library.bookCount++] = Book(t,a,isbn,y);
                    library.saveData();
                    break;
                }
                case 2: {
                    if(library.studentCount >= Library::MAX_STUDENTS) { std::cout << "Student list full!\n"; break; }
                    std::string fn,ln,ad; int id;
                    std::cout << "First Name: "; std::cin >> fn;
                    std::cout << "Last Name: "; std::cin >> ln;
                    std::cout << "ID: "; std::cin >> id;
                    std::cin.ignore();
                    std::cout << "Address: "; std::getline(std::cin,ad);
                    library.students[library.studentCount++] = Student(fn,ln,id,ad);
                    library.saveData();
                    break;
                }
                case 3: {
                    std::string author;
                    std::cin.ignore();
                    std::cout << "Enter author: "; std::getline(std::cin,author);
                    bool found=false;
                    for(int i=0;i<library.bookCount;i++)
                        if(library.books[i].author==author) { std::cout << "- " << library.books[i].title << "\n"; found=true;}
                    if(!found) std::cout << "No books by this author.\n";
                    break;
                }
                case 4: library.generateReport(); break;
                case 5: running=false; break;
                default: std::cout << "Invalid option!\n";
            }
        } else {
            switch(choice) {
                case 1: { // Borrow Book
                    int sID,bISBN;
                    std::cout << "Student ID: "; std::cin >> sID;
                    std::cout << "Book ISBN: "; std::cin >> bISBN;

                    int studentIndex=-1,bookIndex=-1;
                    for(int i=0;i<library.studentCount;i++) if(library.students[i].id==sID) studentIndex=i;
                    for(int i=0;i<library.bookCount;i++) if(library.books[i].isbn==bISBN) bookIndex=i;

                    if(studentIndex==-1 || bookIndex==-1) std::cout << "Student or book not found.\n";
                    else if(library.books[bookIndex].isBorrowed) std::cout << "Book already borrowed.\n";
                    else if(library.students[studentIndex].borrowBook(bISBN)) {
                        library.books[bookIndex].isBorrowed=true;
                        library.books[bookIndex].borrowerId=sID;
                        std::cout << "Book borrowed successfully.\n";
                        library.saveData();
                    } else std::cout << "Borrow limit reached (3 books)!\n";
                    break;
                }
                case 2: { // Check Account
                    int sID; std::cout << "Student ID: "; std::cin >> sID;
                    int studentIndex=-1;
                    for(int i=0;i<library.studentCount;i++) if(library.students[i].id==sID) studentIndex=i;
                    if(studentIndex==-1) std::cout << "Student not found.\n";
                    else library.students[studentIndex].showAccount();
                    break;
                }
                case 3: { // Search Author
                    std::string author; std::cin.ignore(); std::cout << "Enter author: "; std::getline(std::cin,author);
                    bool found=false;
                    for(int i=0;i<library.bookCount;i++) if(library.books[i].author==author){std::cout<<"- "<<library.books[i].title<<"\n";found=true;}
                    if(!found) std::cout << "No books by this author.\n";
                    break;
                }
                case 4: { // Search Title
                    std::string title; std::cin.ignore(); std::cout << "Enter title: "; std::getline(std::cin,title);
                    bool found=false;
                    for(int i=0;i<library.bookCount;i++) if(library.books[i].title.find(title)!=std::string::npos){std::cout<<"- "<<library.books[i].title<<" ("<<library.books[i].author<<")\n";found=true;}
                    if(!found) std::cout << "No books with this title.\n";
                    break;
                }
                case 5: { // Return Book
                    int sID,bISBN;
                    std::cout << "Student ID: "; std::cin >> sID;
                    std::cout << "Book ISBN: "; std::cin >> bISBN;
                    int studentIndex=-1,bookIndex=-1;
                    for(int i=0;i<library.studentCount;i++) if(library.students[i].id==sID) studentIndex=i;
                    for(int i=0;i<library.bookCount;i++) if(library.books[i].isbn==bISBN) bookIndex=i;
                    if(studentIndex==-1 || bookIndex==-1) std::cout << "Student or book not found.\n";
                    else if(library.students[studentIndex].returnBook(bISBN)) {
                        library.books[bookIndex].isBorrowed=false;
                        library.books[bookIndex].borrowerId=0;
                        std::cout << "Book returned successfully.\n";
                        library.saveData();
                    } else std::cout << "This book is not in your borrowed list.\n";
                    break;
                }
                case 6: running=false; break;
                default: std::cout << "Invalid option!\n";
            }
        }
    }

    return 0;
}
