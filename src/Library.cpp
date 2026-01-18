#include "Library.hpp"
#include <fstream>
#include <iostream>

Library::Library() : bookCount(0), studentCount(0) {}

void Library::saveData() {
    std::ofstream bookFile("data/books.txt");
    for(int i=0;i<bookCount;i++) {
        bookFile << books[i].isbn << ";" << books[i].title << ";"
                 << books[i].author << ";" << books[i].publishDate.year << ";"
                 << books[i].isBorrowed << ";" << books[i].borrowerId << "\n";
    }
    bookFile.close();

    std::ofstream studentFile("data/students.txt");
    for(int i=0;i<studentCount;i++) {
        studentFile << students[i].id << ";" << students[i].firstName << ";"
                    << students[i].lastName << ";" << students[i].address << "\n";
    }
    studentFile.close();
}

void Library::loadData() {
    std::ifstream bookFile("data/books.txt");
    if(bookFile.is_open()) {
        while(bookFile >> books[bookCount].isbn) {
            bookFile.ignore();
            std::getline(bookFile, books[bookCount].title, ';');
            std::getline(bookFile, books[bookCount].author, ';');
            bookFile >> books[bookCount].publishDate.year;
            bookFile.ignore();
            bookFile >> books[bookCount].isBorrowed;
            bookFile.ignore();
            bookFile >> books[bookCount].borrowerId;
            bookCount++;
        }
        bookFile.close();
    }

    std::ifstream studentFile("data/students.txt");
    if(studentFile.is_open()) {
        while(studentFile >> students[studentCount].id) {
            studentFile.ignore();
            std::getline(studentFile, students[studentCount].firstName, ';');
            std::getline(studentFile, students[studentCount].lastName, ';');
            std::getline(studentFile, students[studentCount].address);
            studentCount++;
        }
        studentFile.close();
    }
}

void Library::generateReport() {
    std::ofstream report("data/report.txt");
    report << "LIBRARY REPORT\n";
    report << "Total Books: " << bookCount << "\n";
    report << "Total Students: " << studentCount << "\n";
    report << "--------------------------------\n";
    report << "BORROWED BOOKS:\n";

    bool anyBorrowed = false;
    for(int i=0;i<bookCount;i++) {
        if(books[i].isBorrowed) {
            report << "- " << books[i].title << " (ISBN: " << books[i].isbn
                   << ") -> Student ID: " << books[i].borrowerId << "\n";
            anyBorrowed = true;
        }
    }
    if(!anyBorrowed) report << "No books currently borrowed.\n";
    report.close();

    std::cout << "[INFO] Report generated (report.txt).\n";
}
