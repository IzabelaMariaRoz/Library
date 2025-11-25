#include <iostream>
using namespace std;



class Ksiazka : public PozycjaBiblioteczna {
    int rokWydania;
    
    public:
        Ksiazka(string tytul, string autor, int rok)
            : PozycjaBiblioteczna(tytul,autor,rok)

    void wyswietlInfo(){
        // ladne wyswietlanie przy uzyciu biblioteki libfort lub Variadic Table
    }

}

void Wypozycz(string tytul_ksiazki, string user_id, int ilosc){
    // wyciaganie id po tytule

    // return 'Wypozyczono {ilosc} szt. {tytul_ksiazki}'
}

void Zwrot(string tytul_ksiazki, string user_id, int ilosc){
    // wyciaganie id po tytule

    // return 'Zwrocono {ilosc} ksiazek'
}


void Dostepnosc(int id_ksiazki){

 //   if( id_ksiazki in 'ksiazki.txt'  ){
        // return 'Ksiazka dostepna w ilosci: {ilosc}'
//    }
//    else{
        // return 'Ksiazka niedostepna, przepraszamy'
//    }
}

void StworzUzytkownika(string imie, string nazwisko, string mail){
    // id = 3 pierwsze litery imienia i 3 pierwsze litery nazwiska
}




int main(){
    bool continue = true;

    while continue{
        // menu z opcjami
    }

    return 0;
}