#pragma once
#include "Prostokat.h"
#include <vector>


class ListaProstokatow
{
	private:
		std::vector<Prostokat> buttony;

	public:
		void DodajProstokat(unsigned int wysokosc_okna,unsigned int ksztalt_width, unsigned int ksztalt_height, unsigned int X, unsigned int Y, bool przycisk);
		Prostokat ZwrocProstokat(unsigned int i)const;
		const unsigned int IloscProstokatow()const;
		sf::Color ZwrocKolorProstokata(unsigned int index);
		void ZmienKolorProstokata(unsigned int index, int kodKoloru);
		void ZmienKolorProstokata(unsigned int index, sf::Color Kolor);
		void WylaczPrzycisk(unsigned int index);
		void WlaczPrzycisk(unsigned int index, sf::Color kolor, bool czyPodsumowanie);
		void WyczyscListe();
};

