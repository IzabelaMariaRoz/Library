#pragma once
#include <string>
#include <vector>

class Student {
private:
    std::string name;
    std::string lastName;
    int id;
    std::string address;
    std::vector<int> borrowedBooks;

public:
    Student();
    Student(const std::string& name, const std::string& lastName, int id, const std::string& address);

    std::string getFullName() const;
    int getId() const;
    void borrowBook(int isbn);
    bool canBorrow() const;
    void checkBalance() const;

    std::string serialize() const;
    void deserialize(const std::string& data);
};
