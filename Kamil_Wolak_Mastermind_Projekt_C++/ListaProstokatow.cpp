#include "ListaProstokatow.h"

void ListaProstokatow::DodajProstokat(unsigned int wysokosc_okna,unsigned int ksztalt_width, unsigned int ksztalt_height, unsigned int X, unsigned int Y, bool przycisk){
	Prostokat NowyProstokat;
	NowyProstokat.UstawPozycje(X,Y,wysokosc_okna);
	NowyProstokat.UstawRozmiar(ksztalt_width, ksztalt_height);
	NowyProstokat.UstawCzyPrzycisk(przycisk);
	if (przycisk != true)
		NowyProstokat.UstawKolor(-1);
	ListaProstokatow::buttony.push_back(NowyProstokat);
}

Prostokat ListaProstokatow::ZwrocProstokat(unsigned int i)const{
	return ListaProstokatow::buttony[i];
}

const unsigned int  ListaProstokatow::IloscProstokatow()const {
	return ListaProstokatow::buttony.size();
}

sf::Color ListaProstokatow::ZwrocKolorProstokata(unsigned int index){
	return ListaProstokatow::buttony[index].ZwrocKsztalt().getFillColor();
}

void ListaProstokatow::ZmienKolorProstokata(unsigned int index, int kodKoloru){
	ListaProstokatow::buttony[index].UstawKolor(kodKoloru);
}

void ListaProstokatow::ZmienKolorProstokata(unsigned int index, sf::Color Kolor){
	ListaProstokatow::buttony[index].UstawKolor(Kolor);
}

void ListaProstokatow::WylaczPrzycisk(unsigned int index){
	if (ListaProstokatow::buttony[index].CzyPrzycisk() == true){ZmienKolorProstokata(index, -1);}
	ListaProstokatow::buttony[index].UstawCzyPrzycisk(false);
}

void ListaProstokatow::WlaczPrzycisk(unsigned int index, sf::Color kolor, bool czyPodsumowanie){
	if ((index % 3 == 0 || index % 3 == 1) && czyPodsumowanie == false){ListaProstokatow::buttony[index].UstawCzyPrzycisk(true);}
	if (czyPodsumowanie == true) { ListaProstokatow::buttony[index].UstawCzyPrzycisk(true);}
	ZmienKolorProstokata(index,kolor);
}

void  ListaProstokatow::WyczyscListe(){
	ListaProstokatow::buttony.clear();
}