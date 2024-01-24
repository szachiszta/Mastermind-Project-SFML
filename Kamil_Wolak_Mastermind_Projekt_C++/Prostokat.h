#pragma once
#include <SFML/Graphics.hpp>

class Prostokat
{
	private:
		sf::RectangleShape ksztalt;
		bool czy_przycisk;
	
	public:
		void UstawRozmiar(unsigned int ksztalt_width, unsigned int ksztalt_height);
		void UstawPozycje(unsigned int X, unsigned int Y, unsigned int wysokosc_okna);
		void UstawCzyPrzycisk(bool przycisk);
		void UstawKolor(int i);
		void UstawKolor(sf::Color kolor);
		bool CzyPrzycisk()const;
		sf::RectangleShape ZwrocKsztalt()const;
		void UstawObramowanie(const float grubosc, const sf::Color kolor);
};

