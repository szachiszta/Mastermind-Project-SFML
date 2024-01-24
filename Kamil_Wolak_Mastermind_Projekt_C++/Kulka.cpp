#include "Kulka.h"
#include <vector> //do obs³ugi kolorów do wyboru

vector<string> kolory_do_wyboru{ "czerwony","zielony","¿ó³ty","niebieski","fioletowy","br¹zowy"};

void Kulka::UstawKodKoloru(int kodKoloru){
	Kulka::kodKoloru = kodKoloru;
}

void Kulka::UstawKodKoloru(){
	Kulka::kolor = "brak";
	Kulka::kodKoloru = -1; //Dla póŸniejszego zmieniania
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

