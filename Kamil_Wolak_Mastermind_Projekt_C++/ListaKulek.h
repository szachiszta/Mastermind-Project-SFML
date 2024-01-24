#pragma once
#include "kulka.h"
#include <vector>

class ListaKulek
{
	private:
		vector<Kulka> lista_kulek = {};

	public:
		void DodajKulke(int kod_koloru); //dodajemy poszczeg�lne kulki i dodajemy do listy kulek
		void DodajKulke(); // do inicjalizacji pustej listy o okre�lonej liczbie element�w
		string WypiszKulki()const; //wypisujemy wszystkie kolory kulek w ci�gu
		void ZmienKolorKulki(unsigned int index, unsigned int kod_koloru);
		Kulka ZwrocKulke(unsigned int indeks)const;
		void  WyczyscListe();
};

//TODO sprawdzic czy sprawdzkombinacje i Wypiszzkulki potrzebne