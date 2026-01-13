#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

bool borrow(){
    if(borrowedCount<quantity){
        borrowedCount++;
        return true;
    }
    return false;
}

void returnBook(){
    if(borrowedCount>0) borrowedCount--;
}

void searchByTitleInFile(const string& filename, const string& titleQuery) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Nie można otworzyć pliku!\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string isbnStr, title, author, yearStr, quantityStr, borrowedStr;

        getline(ss, isbnStr, ';');
        getline(ss, title, ';');
        getline(ss, author, ';');
        getline(ss, yearStr, ';');
        getline(ss, quantityStr, ';');
        getline(ss, borrowedStr, ';');

        if (title.find(titleQuery) != string::npos) {
            cout << "ISBN: " << isbnStr
                 << ", Tytuł: " << title
                 << ", Autor: " << author
                 << ", Dostępne: " << stoi(quantityStr) - stoi(borrowedStr) << endl;
            found = true;
        }
    }

    if (!found) cout << "Nie znaleziono książki o takim tytule.\n";

    file.close();
}
void searchByAuthorInFile(const string& filename, const string& authorQuery) {
    ifstream file(filename);
    string line;
    bool found = false;


    while (getline(file, line)) {
        stringstream ss(line);
        string isbnStr, title, author, yearStr, quantityStr, borrowedStr;

        getline(ss, isbnStr, ';');
        getline(ss, title, ';');
        getline(ss, author, ';');
        getline(ss, yearStr, ';');
        getline(ss, quantityStr, ';');
        getline(ss, borrowedStr, ';');

        if (author.find(authorQuery) != string::npos) {
            cout << "ISBN: " << isbnStr
                 << ", Tytuł: " << title
                 << ", Autor: " << author
                 << ", Dostępne: " << stoi(quantityStr) - stoi(borrowedStr) << endl;
            found = true;
        }
    }

    if (!found) cout << "Nie znaleziono książki tego autora.\n";
    file.close();
}
