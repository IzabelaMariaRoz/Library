#pragma once
#include "Book.hpp"
#include "Student.hpp"
#include <vector>
#include <string>

class Library {
private:
    std::vector<Book> books;
    std::vector<Student> students;

public:
    void addBook(const Book& book);
    void addStudent(const Student& student);

    bool borrowBook(int studentID, int bookISBN);
    void checkStudentBalance(int studentID) const;

    void loadBooks(const std::string& filename);
    void saveBooks(const std::string& filename) const;

    void loadStudents(const std::string& filename);
    void saveStudents(const std::string& filename) const;
};
