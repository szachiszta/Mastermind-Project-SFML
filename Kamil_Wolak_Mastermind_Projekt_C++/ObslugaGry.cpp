#include "ObslugaGry.h"
#include <iostream> //pozniej moze wylaczyc 
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "includer.h"


unsigned int wysokosc_okna = sf::VideoMode().getDesktopMode().height;
unsigned int szerokosc_okna = sf::VideoMode().getDesktopMode().width;
const unsigned int liczba_kolorow = 6; //Tutaj sta³e //1920 x 1036
static unsigned int liczba_kulek = 1;
static unsigned int liczba_prob = 1;


int * kodKoloruUstaw = new int[liczba_kulek];	// Po podsumowaniu ustawiamy kolory kulek na odpowiedni kolor (zeby nastêpna próba miala ju¿ kolory)
int * tablicaZgodnosci = new int[liczba_kulek]; // Tablica wyników zawiera dane na temat zgodnoœci kulek zgadywanych z kulkami wylosowanymi (diody)
vector<int> TablicaKodowZgadywanych = {}; //zawiera kody kolorow dla zgadywanej próby
vector<int> TablicaKodowWylosowanych = {}; //zawiera kody kolorów dla wylosowanej próby


void ustawLiczba_kulek(const unsigned int liczba_kulekUstaw, const unsigned int liczba_probUstaw) {
	liczba_kulek = liczba_kulekUstaw;
	liczba_prob = liczba_probUstaw;
}

unsigned int ObslugaWydarzenKlikniecia(sf::RenderWindow& window, sf::Event& event, ListaProstokatow& listaProstokatow, ListaProstokatow& listaPodsumowan, 
									   ListaProstokatow& listaWynikow, ListaKulek& listaKulekTypowana, ListaKulek& listaKulekWylosowana, unsigned int& proba, 
									   sf::Sprite& panel, sf::Texture& teksturaPrzegrana, sf::Texture& teksturaWygrana) {
	//Obs³uga klikniêæ przycisków zmieniaj¹cych wartoœci kulek
	for (int i = 0; i < (liczba_kulek * liczba_prob * 3); i += 1) { //razy 3 poniewaz 3 s¹ klawisze na jeden obiekt kulki
		if (Kliknieto(listaProstokatow.ZwrocProstokat(i), window, event)) {	//w parametrze jaki kszta³t jest buttonem, wskaznik do okna i event (odpowiedzialne za obsluge eventow)
			ZmienKodKulki(i, listaProstokatow); // Je¿eli kliknelismy button zmiany koloru (strzalka) wtedy zmieniami kolor kulki (tylko wizualny) -> kod koloru zmienia siê w podsumowaniu
			//jak nie znajdzie -1 to aktywuje przycisk (wszystkie kulki wybrane)
			bool ustawAktywny = true;
			for (int i = 0; i < liczba_kulek; i++){
				if (kodKoloruUstaw[i] == -1) {ustawAktywny = false;}
			}	 
			if (ustawAktywny == true) { listaPodsumowan.WlaczPrzycisk(proba, sf::Color::White, true);}
			
			return 1;
		}
	}
	//obs³uga klikniêæ przycisków submit
	for (int i = 0; i < liczba_prob; i++) {
		if (Kliknieto(listaPodsumowan.ZwrocProstokat(i), window, event)) {
			cout << "Submit próba " << i << endl;
			if (PodsumowanieProby(listaKulekTypowana, listaKulekWylosowana, proba, listaProstokatow, listaPodsumowan) == true) {
				panel.setTexture(teksturaWygrana); //ustawiamy sprite na ca³y ekran Do zmiany tekstuwy porazki i zwyciestwa
				panel.setScale(sf::Vector2f(float(sf::VideoMode().getDesktopMode().width) / float(teksturaWygrana.getSize().x), float(sf::VideoMode().getDesktopMode().height) / float(teksturaWygrana.getSize().y)));
				return 2; //Status gry na 3 (restart gry albo wyjdz do menu)
			}
			else if(proba == liczba_prob){
				panel.setTexture(teksturaPrzegrana); //ustawiamy sprite na ca³y ekran Do zmiany tekstuwy porazki i zwyciestwa
				panel.setScale(sf::Vector2f(float(sf::VideoMode().getDesktopMode().width) / float(teksturaPrzegrana.getSize().x), float(sf::VideoMode().getDesktopMode().height) / float(teksturaPrzegrana.getSize().y)));
				return 3; // status gry 3 (restart gry albo wyjdz do menu)
			}
			UstawWyniki(proba, listaWynikow);
			return 4;
		}
	}
	return 0;
}

void TworzenieList(ListaProstokatow& listaProstokatow, ListaProstokatow& listaPodsumowan, ListaProstokatow& listaWynikow) {

	float szerokosc_p = (szerokosc_okna * 0.30) / (liczba_kulek); //Procent zajêcia szerokosci ekranu przez przyciski (okolo 60%)
	float wysokosc_p = (wysokosc_okna * 0.55) / (liczba_prob);    //Procent zajecia wysokosci ekranu przez przyciski ( okolo 80 %)
	float X = szerokosc_okna * 0.15;
	float Y = 0;
	//cout << listaProstokatow.ZwrocRozmiarTablicy();
	//Tworzenie wszystkich prostok¹tów dla kulek i przycisków zmiany
	for (int i = 0; i < liczba_kulek * liczba_prob; i++) {
		if (i % (liczba_kulek) == 0) {
			Y += 1.75 * wysokosc_p;
			X = szerokosc_okna * 0.1; //Pocz¹tkowa pozycja dla 1 obiektu w rzêdzie
		}
		listaProstokatow.DodajProstokat(wysokosc_okna, szerokosc_p * 0.3, wysokosc_p, X - (szerokosc_p * 0.30), Y, true); // lewy przycisk
		listaProstokatow.DodajProstokat(wysokosc_okna, szerokosc_p * 0.3, wysokosc_p, X + (szerokosc_p), Y, true); // prawy przycisk
		listaProstokatow.DodajProstokat(wysokosc_okna, szerokosc_p, wysokosc_p, X, Y, false); // Œrodkowy obrazek (tutaj wyswietlimy kolory kulek)
		X += 2 * szerokosc_p; //przerwa miedzy kolejn¹ seri¹ 3 obiektów
	}
	unsigned int Koniec_kulki = X + szerokosc_p;
	//Tworzenie wszystkich przycisków submitów
	X = Koniec_kulki;
	Y = 1.5 * wysokosc_p;
	for (int i = 0; i < liczba_prob; i++) {
		listaPodsumowan.DodajProstokat(wysokosc_okna, szerokosc_p, wysokosc_p * 0.5, X, Y, false);//domyslnie wylacz
		Y += 1.75 * wysokosc_p; //Ustalamy odstêp pomiêdzy przyciskami
	}
	unsigned int Koniec_podsumowan = X + szerokosc_p * 1.5f;

	//Tworzenie wszystkich kwadratow wynikow
	X = Koniec_podsumowan + (liczba_kulek * 0.15 * szerokosc_p);
	Y = 1.2 * wysokosc_p;
	for (int i = 0; i < liczba_prob * liczba_kulek; i++) {
		listaWynikow.DodajProstokat(wysokosc_okna, szerokosc_p * 0.1, wysokosc_p * 0.1, X, Y, true);
		listaWynikow.ZmienKolorProstokata(i, -1);

		if (i % 2 == 0) {
			Y += 0.20f * wysokosc_p;
		}
		else {
			X -= 0.2f * szerokosc_p;
			Y -= 0.20f * wysokosc_p;
		}

		if ((i + 1) % liczba_kulek == 0 && i != 0) {
			Y += 1.75f * wysokosc_p;
			X = Koniec_podsumowan + (liczba_kulek * 0.15 * szerokosc_p);
		}
	}
}

//Obs³uga klikniêcia w przycisk
bool Kliknieto(Prostokat prostokat, sf::RenderWindow& window, sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (event.mouseButton.x > prostokat.ZwrocKsztalt().getPosition().x &&
				event.mouseButton.x < prostokat.ZwrocKsztalt().getPosition().x + prostokat.ZwrocKsztalt().getSize().x &&
				event.mouseButton.y > prostokat.ZwrocKsztalt().getPosition().y &&
				event.mouseButton.y < prostokat.ZwrocKsztalt().getPosition().y + prostokat.ZwrocKsztalt().getSize().y &&
				prostokat.CzyPrzycisk() == true) {
				return true;
			}
		}
	}
	return false;
}

bool Najechano(Prostokat prostokat, sf::RenderWindow& window) {
	if (sf::Mouse::getPosition(window).x > prostokat.ZwrocKsztalt().getPosition().x &&
		sf::Mouse::getPosition(window).x < prostokat.ZwrocKsztalt().getPosition().x + prostokat.ZwrocKsztalt().getSize().x &&
		sf::Mouse::getPosition(window).y > prostokat.ZwrocKsztalt().getPosition().y &&
		sf::Mouse::getPosition(window).y < prostokat.ZwrocKsztalt().getPosition().y + prostokat.ZwrocKsztalt().getSize().y &&
		prostokat.CzyPrzycisk() == true) {
		return true;
	}
	return false;
}


void GenerowanieKulek(ListaKulek& listaKulekWylosowana, ListaKulek& listaKulekTypowana) {
	int wylosowana;
	for (int i = 0; i < liczba_kulek; i++) {
		wylosowana = rand() % liczba_kolorow;
		listaKulekWylosowana.DodajKulke(wylosowana); //losujemy liczby od 0 do 5 dla 6 mo¿liwych kolorów naszych kul
		listaKulekTypowana.DodajKulke();
	}
	cout << "wylosowano kombinacje " << listaKulekWylosowana.WypiszKulki()<<endl;
}

//Dla samego poczatku wylaczenie wszystkich oprocz przycisków dla 1 próby:
void AktywacjaPrzyciskow(ListaProstokatow& listaProstokatow, ListaProstokatow& listaPodsumowan) {
		for (int i = liczba_kulek * 3; i < liczba_kulek * 3 * liczba_prob; i++) {listaProstokatow.WylaczPrzycisk(i);}
}

void AktywacjaPrzyciskow(ListaProstokatow& listaProstokatow, ListaProstokatow& listaPodsumowan, unsigned int& proba) {
	if(proba < liczba_prob - 1){
		for (int i = 0; i < liczba_kulek * 3; i++) {
			if(i % 3 == 2) //Wlaczamy przyciski dla nastepnej proby i ustawiamy kolor na kolor poprzedniej próby (na jakim skonczylismy (jezeli jest to kulka (bo kulka drukowana jako 3 przycisk)))
				listaProstokatow.WlaczPrzycisk(i + ((proba + 1) * liczba_kulek * 3), listaProstokatow.ZwrocKolorProstokata(i + (liczba_kulek * proba * 3)),false);
			else { //Je¿eli nie jest to kulka to wlaczamy przycisk i zmianiamy kolor na bia³y (z domyœlnie szarego dla wylaczanych przyciskow))
				listaProstokatow.WlaczPrzycisk(i + ((proba + 1) * liczba_kulek * 3), sf::Color::White, false);
			}
		}
		listaPodsumowan.WlaczPrzycisk(proba + 1, sf::Color::White ,true);
	}
	//Wylaczamy przyciski po zakonczeniu proby (dla zakonczonej proby 1 przyciski 1 proby wylaczone)
	for (int i = 0; i < liczba_kulek * 3; i++) {
		listaProstokatow.WylaczPrzycisk(i + (proba * liczba_kulek * 3));
	}
	listaPodsumowan.WylaczPrzycisk(proba);
	proba++; // przechodzimy do nastepnej proby
}

void ZmienKodKulki(int indeks, ListaProstokatow& listaprostokatow) {
	int liczba_do_dodania = 0;
	unsigned int rzad = 0; // w ktorym rzedzie jest przycisk ktoremu chcemy zmieniac kolor
	for (int i = 0; i < liczba_prob; i++) {
		if (indeks >= liczba_kulek * 3) {
			indeks = indeks - (liczba_kulek * 3);
			rzad++;
		}
		else {
			if (indeks % 3 == 0) {
				liczba_do_dodania = -1;	//je¿eli przycisk od lewej odejmujemy
			}
			if (indeks % 3 == 1) {
				liczba_do_dodania = 1; //je¿eli przycisk od prawej odejmujemy
			}
			indeks = (int)indeks / 3; //Dzielimy ca³kowicie przez 3 aby uzyskaæ indeks naszej kulki (poniewa¿ 3 kwadraty na 1 kulkê przypadaj¹)

			//Dodawanie wartoœci kodów kolorów dla poszczególnych kulek i zabezpieczenie przed wyjœciem poza przedzia³
			if (kodKoloruUstaw[indeks] <= 0 && liczba_do_dodania == -1) {kodKoloruUstaw[indeks] = (liczba_kolorow - 1);}
			else if (kodKoloruUstaw[indeks] >= (liczba_kolorow - 1) && liczba_do_dodania == 1) {kodKoloruUstaw[indeks] = 0;}
			else {kodKoloruUstaw[indeks] += liczba_do_dodania;}
			//Tutaj zmieniamy kolor kulki	 //Przycisk pierwszy na 2 miejscu zawsze powtarza sie co 3 i przesuniecie o rz¹d (wiêc przesuwamy o rz¹d * liczba elementów do przesuwania)
			listaprostokatow.ZmienKolorProstokata((2 + (3 * indeks) + rzad * liczba_kulek * 3), kodKoloruUstaw[indeks]);
			return;
		}
	}
}

void InicjacjaKulek() {
	for (int i = 0; i < liczba_kulek; i++) {
		kodKoloruUstaw[i] = -1;
	}
}

//Do wprowadzenia czy zgadza siê kombinacja kulek
// 0 - kulka o takim kolorze nie wystêpuje w kombinacji
// 1 - kulka o takim kolorze wystêpuje w innym miejscu kombinacji
// 2 - kulka o takim kolorze wystêpuje dok³adnie w tym miejscu
//Na koñcu bêdziemy mieszali tablicê aby uzyskaæ losowe miejsce naszych kwadracików


void TablicaZgodnosci(ListaKulek& listaKulekZgadywana, ListaKulek& listaKulekWylosowana, unsigned int& proba){
	ustawTablice(); // na koncu wyzerowac tablice po poprzedniej probie

	if (proba != 0) {
		TablicaKodowWylosowanych.clear(); // czyscimy po poprzedniej probie i uzupelniamy
		TablicaKodowZgadywanych.clear();
	}
	
	for (int i = 0; i < liczba_kulek; i++) {
		TablicaKodowWylosowanych.push_back(listaKulekWylosowana.ZwrocKulke(i).ZwrocKodKoloru());
		TablicaKodowZgadywanych.push_back(listaKulekZgadywana.ZwrocKulke(i).ZwrocKodKoloru());
	}

	//Sprawdzamy 2 pierwsze bo s¹ wa¿niejsze (zeby nie bylo problemow z kolejnoscia sprawdzania)
	for (int i = 0; i < liczba_kulek; i++) {
		if (TablicaKodowWylosowanych[i] == TablicaKodowZgadywanych[i]) {
			tablicaZgodnosci[i] = 2;
			TablicaKodowWylosowanych[i] = -1;
			TablicaKodowZgadywanych[i] = -1;
		}
	}

	for (int i = 0; i < liczba_kulek; i++) {
		for (int j = 0; j < liczba_kulek; j++) {
			if (TablicaKodowWylosowanych[i] == TablicaKodowZgadywanych[j] && TablicaKodowWylosowanych[i] != -1) { //Tablica kodow jako kopia zgadywanej kombinacji
				tablicaZgodnosci[i] = 1;
				TablicaKodowWylosowanych[i] = -1; //"usuwamy" parê kulek ¿eby nie mialy wplywu na reszte losowan
				TablicaKodowZgadywanych[j] = -1;
			}// w przeciwnym wypadku pozostaje 0 czyli nie wyst¹pi³ dany kolor
		}
	}

	for (int i = 0; i < liczba_kulek; i++) {
		cout << TablicaKodowWylosowanych[i] << " ";

	}
	cout << endl;
	for (int i = 0; i < liczba_kulek; i++) {
		cout << TablicaKodowZgadywanych[i] << " ";
	}
	// Przed pomieszaniem
	cout << endl;
	for (int i = 0; i < liczba_kulek; ++i)
		cout << tablicaZgodnosci[i] << " ";
	cout << endl;

	//Po pomieszaniu
	mieszanieTablicy(tablicaZgodnosci, liczba_kulek);
}

//Funkcja do przemieszania tablicy
void mieszanieTablicy(int tablica[], int n){
	srand(time(0)); //dzialamy na zmiennych losowych
	random_shuffle(tablica, tablica + n); //mieszamy losowo tablice
}

bool sprawdzTablice() {
	for (int i = 0; i < liczba_kulek; i++) {
		if (tablicaZgodnosci[i] != 2) {
			return false;
		}
	}
	return true;
}

void UstawWyniki(unsigned int& proba, ListaProstokatow& listawynikow) {
	//cout<<listaKulekWylosowana.WypiszKulki();
	for (int i = 0; i < liczba_kulek; i++) {
		//cout << tablicaZgodnosci[i]<<"  ";
		if (tablicaZgodnosci[i] == 2) {
			listawynikow.ZmienKolorProstokata(i + (proba - 1) * liczba_kulek, 0);
		}
		if (tablicaZgodnosci[i] == 1) {
			listawynikow.ZmienKolorProstokata(i + (proba - 1) * liczba_kulek, 100);
		}	
	}
}

void ustawTablice() {
	for (int i = 0; i < liczba_kulek; i++) {
		tablicaZgodnosci[i] = 0;
	}
}

bool PodsumowanieProby(ListaKulek& listaKulek, ListaKulek& listaKulekWylosowana, 
unsigned int& proba, ListaProstokatow& listaProstokatow, ListaProstokatow& listaPodsumowan) {

	for (int i = 0; i < liczba_kulek; i++) {
		if (kodKoloruUstaw[i] == -1) {
			cout << "Niektóre kulki nie zosta³y wybrane !!";
			listaPodsumowan.WylaczPrzycisk(proba);
			return false;
		}
		listaKulek.ZmienKolorKulki(i, kodKoloruUstaw[i]);
		//Dezaktywacja przycisków i aktywacja nastêpnych
	}

	AktywacjaPrzyciskow(listaProstokatow, listaPodsumowan, proba);
	TablicaZgodnosci(listaKulek, listaKulekWylosowana, proba);

	if (sprawdzTablice() == true)
	{
		cout << "\n=============Gratulacje wygrales=========="<<endl;
		return true;
	}

	if (proba == liczba_prob - 1) {
		//Koniec event 
		cout << "Koniec przegra³eœ";
		cout << proba;
		return false;
	}

	string wynik;
	wynik = listaKulek.WypiszKulki();
	cout << wynik;
	return false;
}


ListaProstokatow WyswietlPoprawneKulki(ListaKulek& listaKulekWylosowana) {
	//Tworzymy obiekty dla wszystkich wylosowanych kulek
	ListaProstokatow listaPrawidlowych;
	unsigned int X = szerokosc_okna / 2 - ((szerokosc_okna * 0.35) / 2);
	unsigned int Y = wysokosc_okna / 1.75;

	for (int i = 0; i < liczba_kulek; i++) {
		listaPrawidlowych.DodajProstokat(wysokosc_okna, (szerokosc_okna * 0.30) / (liczba_kulek), (wysokosc_okna * 0.55) / (liczba_prob), X + (i * (szerokosc_okna * 0.35) / (liczba_kulek)), Y,0);
		listaPrawidlowych.ZmienKolorProstokata(i, listaKulekWylosowana.ZwrocKulke(i).ZwrocKodKoloru());
	}
	cout << "ile dziadow " << listaPrawidlowych.IloscProstokatow();
	return listaPrawidlowych;
}


void WyczyscDane() {
	int* nowa_tablicaZgodnosci = new int[liczba_kulek] {};
	int* nowa_kodKoloruUstaw = new int[liczba_kulek] {};

	// Zwolnij poprzedni¹ tablicê
	delete[] tablicaZgodnosci;
	delete[] kodKoloruUstaw;
	// Przypisz now¹ tablicê jako aktualn¹ tablicê
	tablicaZgodnosci = nowa_tablicaZgodnosci;
	kodKoloruUstaw = nowa_kodKoloruUstaw;

}