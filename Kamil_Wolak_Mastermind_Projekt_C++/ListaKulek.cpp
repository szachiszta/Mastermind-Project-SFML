#include "ListaKulek.h"
#include "Kulka.h"

void ListaKulek::DodajKulke(int kod_koloru){
	Kulka kulka;
	kulka.UstawKodKoloru(kod_koloru);
	kulka.UstawKolor();
	ListaKulek::lista_kulek.push_back(kulka); //Dodajemy ustawion¹ kulke z kolorem na podstawie kodu do listy kulek
}

void ListaKulek::DodajKulke(){ //Dodawanie kulet "pustych"
	Kulka kulka;
	kulka.UstawKodKoloru();
	ListaKulek::lista_kulek.push_back(kulka); 
}

//wypisujemy wszystkie kolory kulek w ci¹gu
string ListaKulek::WypiszKulki()const{
	string wszystkieKulki = "";
	for (Kulka kulka : ListaKulek::lista_kulek) { wszystkieKulki.append(kulka.ZwrocKolor());}
	return wszystkieKulki;
} 

void ListaKulek::ZmienKolorKulki(unsigned int index, unsigned int kod_koloru){
	if (index <= lista_kulek.size()){ //poniewa¿ indeksujemy od 0 a size podaje liczbê elementów do <=
		lista_kulek[index].UstawKodKoloru(kod_koloru);
		lista_kulek[index].UstawKolor();
	}
}

Kulka ListaKulek::ZwrocKulke(unsigned int indeks)const{
	return ListaKulek::lista_kulek[indeks];
}

void  ListaKulek::WyczyscListe() {
	ListaKulek::lista_kulek.clear();
}