#include "Prostokat.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void Prostokat::UstawRozmiar(unsigned int ksztalt_width, unsigned int ksztalt_height) {
	ksztalt.setSize(sf::Vector2f(ksztalt_width, ksztalt_height));
}

void Prostokat::UstawPozycje(unsigned int X, unsigned int Y, unsigned int wysokosc_okna) {
	ksztalt.setPosition(sf::Vector2f(0 + X, wysokosc_okna - Y));
}

sf::RectangleShape Prostokat::ZwrocKsztalt()const{
	return Prostokat::ksztalt;
}

void Prostokat::UstawCzyPrzycisk(bool przycisk) {
	if (przycisk == true) {
		Prostokat::czy_przycisk = true;
	}
	else {
		Prostokat::czy_przycisk = false;
	}
}

bool Prostokat::CzyPrzycisk()const {
	return Prostokat::czy_przycisk;
}

//vector<string> kolory_do_wyboru{ "czerwony","zielony","¿ó³ty","niebieski","fioletowy","br¹zowy"};
void Prostokat::UstawKolor(int i) {
	
	switch (i)
	{
	case -1:
		Prostokat::ksztalt.setFillColor(sf::Color(62, 65, 63,255));
		break;
	case 0:
		Prostokat::ksztalt.setFillColor(sf::Color(255, 0, 0,255));
		break;
	case 1:
		Prostokat::ksztalt.setFillColor(sf::Color(0, 255, 0,255));
		break;
	case 2:
		Prostokat::ksztalt.setFillColor(sf::Color(255, 255, 0,255));
		break;
	case 3:
		Prostokat::ksztalt.setFillColor(sf::Color(0, 0, 255,255));
		break;
	case 4:
		Prostokat::ksztalt.setFillColor(sf::Color(128, 0, 128,255));
		break;
	case 5:
		Prostokat::ksztalt.setFillColor(sf::Color(139, 69, 19,255));
		break;
	case 100:
		Prostokat::ksztalt.setFillColor(sf::Color(255, 255, 255,255));
		break;

	default:
		Prostokat::ksztalt.setFillColor(sf::Color(230, 230, 250,255));
		break;
	}
}

void Prostokat::UstawKolor(sf::Color kolor) {
	Prostokat::ksztalt.setFillColor(kolor);
}

void Prostokat::UstawObramowanie(const float grubosc, const sf::Color kolor) {
	Prostokat::ksztalt.setOutlineThickness(grubosc);
	Prostokat::ksztalt.setOutlineColor(kolor);
	
}


// Prostokat::ksztalt.setFillColor(sf::Color(255, 0, 0)); -> czerwony
// Prostokat::ksztalt.setFillColor(sf::Color(0, 255, 0)); -> zielony
// Prostokat::ksztalt.setFillColor(sf::Color(255, 255, 0)); -> zó³ty
// Prostokat::ksztalt.setFillColor(sf::Color(0, 0, 255)); -> niebieski
// Prostokat::ksztalt.setFillColor(sf::Color(128, 0, 128)); -> fioletowy
// Prostokat::ksztalt.setFillColor(sf::Color(139, 69, 19)); -> br¹zowy
