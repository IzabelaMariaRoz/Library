#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Book {
public:
    string title;
    string author;
    string isbn;
    int yearOfPublishing;
    Book(string title,string author, string isbn,int yearOfPublishing) {
        this ->title = title;
        this ->author = author;
        this ->isbn = isbn;
        this ->yearOfPublishing = yearOfPublishing;
    }
// Otwieramy plik w trybie dopisywania na koncu
// Dopisujemy do pliku tytul oraz autora ksiazki oraz trzy pierwsze znaki isbn
    void addCopies(int amount) {
        ofstream file;
        file.open("books.txt", ios::app);
        for (int i = 0; i < amount; i++) {
            file << endl << title + " " + author + " " + isbn.substr(0,3);
        }
    }
};

// Sprawdzanie kazdej linii w pliku z dostepnymi ksiazkami
// Jezeli linia nie posiada szukanego przez nas tytulu zwraca string::npos lub jesli posiada, dodaje 1 do liczby kopii
void TitleSearch(string title=""){
    if (title==""){
        cout << "No title included.\n";
        return;
    }
    int book_count = 0;
    string line;
    ifstream file;
    file.open("books.txt", ios::in);
    while (getline(file, line)) {
        if (line.find(title) != string::npos) 
            book_count++;
    }
    file.close();
    cout << "We have " + to_string(book_count) + " copies of " + title << endl;
}

// Sprawdzanie kazdej linii w pliku z dostepnymi ksiazkami
// Jezeli linia posiada szukanego autora dodaje 1 do liczby ksiazek tego autora
// Aby ksiazki o tym samym tytule nie byly liczone za kazdym razem sprawdzana jest poprzednia linia
void AuthorSearch(string author=""){
    if (author==""){
        cout << "No author included.\n";
        return;
    }
    int book_count = 0;
    string last_line = "";
    string line;
    ifstream file;
    file.open("books.txt", ios::in);
    while (getline(file, line)) {
        if (line.find(author) != string::npos and line != last_line) 
            book_count++;
            last_line = line;
    }
    file.close();
    cout << "We have " + to_string(book_count) + " books made by " + author << endl;
}

int main(){
    TitleSearch("Krzyzacy");
    AuthorSearch("Adam Mickiewicz");
    Book ksiazka("Pan Tadeusz","Adam Mickiewicz","1233",1834);
    ksiazka.addCopies(3);
    return 0;
}
