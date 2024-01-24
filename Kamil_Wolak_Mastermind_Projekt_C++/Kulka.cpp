#include "Kulka.h"
#include <vector> //do obs�ugi kolor�w do wyboru

vector<string> kolory_do_wyboru{ "czerwony","zielony","��ty","niebieski","fioletowy","br�zowy"};

void Kulka::UstawKodKoloru(int kodKoloru){
	Kulka::kodKoloru = kodKoloru;
}

void Kulka::UstawKodKoloru(){
	Kulka::kolor = "brak";
	Kulka::kodKoloru = -1; //Dla p�niejszego zmieniania
}

string Kulka::ZwrocKolor()const{
	return Kulka::kolor;
}

const int Kulka::ZwrocKodKoloru()const {
	return Kulka::kodKoloru;
}

void Kulka::UstawKolor(){
	if (Kulka::kodKoloru == -1) {Kulka::kolor = "brak";}
	else{Kulka::kolor = kolory_do_wyboru[Kulka::kodKoloru];}
}

