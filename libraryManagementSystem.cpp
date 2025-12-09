#include <iostream>

// Student class
class Student {
    public: 
        std::string name;
        std::string lastName;
        int id;
        std::string address;

        Student(std::string name,std::string lastName, int id,std::string address) {
            this->name = name;
            this ->lastName = lastName;
            this->id = id;
            this->address = address;
        }
        // Check book balance
        // void checkBalance(int id) {
        // }
};

// Book class
class Book {
    public:
        std::string title;
        std::string author;
        int isbn;
        int yearOfPublishing;
    Book(std::string title,std::string author, int isbn,int yearOfPublishing) {
        this ->title = title;
        this ->author = author;
        this ->isbn = isbn;
        this ->yearOfPublishing = yearOfPublishing;
    }
};

// DATABASES
// All saved to txt files
// All student objects are contained in a students array of max size = 7
// All book objects are contained in a library array of max size = 10


// FUNCTIONS
// (...)

int main() {
    std::cout << "-------------------------------WELCOME TO THE LIBRARY SYSTEM-------------------------------" << '\n';
    // 1.Switch between admin and student
    // 2.Multiple option menu
    return 0;
}