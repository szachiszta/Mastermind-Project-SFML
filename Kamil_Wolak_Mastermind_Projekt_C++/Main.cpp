#include <iostream>
#include "ListaKulek.h"
#include "ListaProstokatow.h"
#include "ObslugaGry.h"
#include <time.h>
#include <windows.h>
#include "includer.h"

//Dla 0 dodajemy -1 do kulki na miejscu[0]
//Dla 1 dodajemy +1 do kulki na miejscu[0]
//Dla 2 dodajemy -1 do kulki na miejscu[1]
//Dla 3 dodajemy +1 do kulki na miejscu[1]   £¥CZNIE 4 KULKI
//Dla 4 dodajemy -1 do kulki na miejscu[2]
//Dla 5 dodajemy +1 do kulki na miejscu[2]
//Dla 6 dodajemy -1 do kulki na miejscu[3]
//Dla 7dodajemy +1 do kulki na miejscu[3]
//                                             (Poniewa¿ 3 to sta³a liczba przycisków wyswietlana dla 1 kulki)
//Je¿eli indeks jest wiêkszy od (liczbaKulek * 3)  <==> odejmujemy dopóki nie otrzymamy liczby od której nie mo¿emy odj¹æ (¿eby znaleŸæ indeks kulki który bêdziemy chcieli zmieniaæ)
// Wtedy co 4 bêdziemy musieli zmieniaæ indeks naszej kulki do której bêdziemy dodawali

int main() {
	
	///////PRZYCISKI OBS£UGUJ¥CE MENU, EKRAN KOÑCOWY///////////////////////
	Prostokat przyciskTrybLatwy;
	Prostokat przyciskTrybTrudny;
	Prostokat przyciskWyjdz;
	Prostokat przyciskWyjdzDoMenu;
	Prostokat przyciskPonownie;
	Prostokat wyjscieZGry;
	przyciskTrybLatwy.UstawRozmiar(sf::VideoMode().getDesktopMode().width / 5, sf::VideoMode().getDesktopMode().height / 10);
	przyciskTrybLatwy.UstawKolor(sf::Color::Transparent);
	przyciskTrybLatwy.UstawPozycje(sf::VideoMode().getDesktopMode().width / 2 - (przyciskTrybLatwy.ZwrocKsztalt().getSize().x / 2), sf::VideoMode().getDesktopMode().height / 3, sf::VideoMode().getDesktopMode().height);
	przyciskTrybLatwy.UstawCzyPrzycisk(true);
	przyciskTrybLatwy.UstawObramowanie(5, sf::Color::White);
	przyciskTrybTrudny.UstawRozmiar(sf::VideoMode().getDesktopMode().width / 5, sf::VideoMode().getDesktopMode().height / 10);
	przyciskTrybTrudny.UstawKolor(sf::Color::Transparent);
	przyciskTrybTrudny.UstawPozycje(przyciskTrybLatwy.ZwrocKsztalt().getPosition().x, sf::VideoMode().getDesktopMode().height / 3 + przyciskTrybLatwy.ZwrocKsztalt().getSize().y * 1.2, sf::VideoMode().getDesktopMode().height);
	przyciskTrybTrudny.UstawCzyPrzycisk(true);
	przyciskTrybTrudny.UstawObramowanie(5, sf::Color::White);
	przyciskWyjdz.UstawRozmiar(sf::VideoMode().getDesktopMode().width / 5, sf::VideoMode().getDesktopMode().height / 10);
	przyciskWyjdz.UstawKolor(sf::Color::Transparent);
	przyciskWyjdz.UstawPozycje(przyciskTrybLatwy.ZwrocKsztalt().getPosition().x, sf::VideoMode().getDesktopMode().height / 3 - przyciskTrybLatwy.ZwrocKsztalt().getSize().y * 1.2, sf::VideoMode().getDesktopMode().height);
	przyciskWyjdz.UstawCzyPrzycisk(true);
	przyciskWyjdz.UstawObramowanie(5, sf::Color::White);
	przyciskWyjdzDoMenu.UstawRozmiar(sf::VideoMode().getDesktopMode().width / 3, sf::VideoMode().getDesktopMode().height / 10);
	przyciskWyjdzDoMenu.UstawKolor(sf::Color::Transparent);
	przyciskWyjdzDoMenu.UstawPozycje((sf::VideoMode().getDesktopMode().width / 2) - (przyciskWyjdzDoMenu.ZwrocKsztalt().getSize().x / 2), sf::VideoMode().getDesktopMode().height / 3.5, sf::VideoMode().getDesktopMode().height);
	przyciskWyjdzDoMenu.UstawCzyPrzycisk(true);
	przyciskWyjdzDoMenu.UstawObramowanie(5, sf::Color::White);
	przyciskPonownie.UstawRozmiar(sf::VideoMode().getDesktopMode().width / 3, sf::VideoMode().getDesktopMode().height / 10);
	przyciskPonownie.UstawKolor(sf::Color::Transparent);
	przyciskPonownie.UstawPozycje((sf::VideoMode().getDesktopMode().width / 2) - (przyciskWyjdzDoMenu.ZwrocKsztalt().getSize().x / 2), sf::VideoMode().getDesktopMode().height / 2.35, sf::VideoMode().getDesktopMode().height);
	przyciskPonownie.UstawCzyPrzycisk(true);
	przyciskPonownie.UstawObramowanie(5, sf::Color::White);
	wyjscieZGry.UstawRozmiar(40, 40);
	wyjscieZGry.UstawPozycje(10, sf::VideoMode().getDesktopMode().height - 10, sf::VideoMode().getDesktopMode().height);
	wyjscieZGry.UstawCzyPrzycisk(true);
	
	/////////LISTY ZAWIERAJ¥CE OBIEKTY DO WYDRUKOWANIA I OBS£UGI///////////////////
	ListaKulek listaKulekWylosowana;
	ListaKulek listaKulekTypowana;
	ListaProstokatow listaProstokatow;
	ListaProstokatow listaPodsumowan;
	ListaProstokatow listaWynikow;
	ListaProstokatow listaProstokatowPoprawna;
	sf::RectangleShape aktualnie_drukowany; //do drukowania otuksterowanego obiektu

	////////////////TEKSTURY £ADOWANIE I TWORZENIE OBIEKTÓW///////////////////////
	sf::Sprite panel; //Okno dla komunikatow 
	panel.setPosition(sf::Vector2f(0, 0));
	sf::Texture teksturaMenu;
	sf::Texture teksturaPrzegrana;
	sf::Texture teksturaWygrana;
	sf::Texture teksturaStrzalkaLewo;
	sf::Texture teksturaStrzalkaPrawo;
	sf::Texture teksturaKulka;
	sf::Texture teksturaKulkaPodsumowanie;
	sf::Texture teksturaPodsumowanie;
	sf::Texture teksturaZamknij;
	teksturaMenu.loadFromFile("tekstury/menu.png");
	teksturaPrzegrana.loadFromFile("tekstury/przegrana.png");
	teksturaWygrana.loadFromFile("tekstury/wygrana.png");
	teksturaStrzalkaLewo.loadFromFile("tekstury/lewo.png");
	teksturaStrzalkaPrawo.loadFromFile("tekstury/prawo.png");
	teksturaKulka.loadFromFile("tekstury/kula.png");
	teksturaKulkaPodsumowanie.loadFromFile("tekstury/kulakoniec.png");
	teksturaPodsumowanie.loadFromFile("tekstury/podsumowanie.png");
	teksturaZamknij.loadFromFile("tekstury/zamknij.png");

	////////////////MUZYKA i DWIÊKI///////////////////////////
	sf::Music muzyka;
	muzyka.openFromFile("dzwieki/Dead_Wrong_Jeremy_Blake.mp3");
	muzyka.setLoop(true);
	muzyka.setVolume(40);
	sf::SoundBuffer klikniecieBuffer;
	sf::SoundBuffer kliknieciePodsumowanieBuffer;
	sf::SoundBuffer przegranaBuffer;
	sf::SoundBuffer wygranaBuffer;
	sf::Sound dzwiekKlikniecie;
	sf::Sound dzwiekPodsumowanie;
	sf::Sound dzwiekPrzegrana;
	sf::Sound dzwiekWygrana;
	dzwiekKlikniecie.setVolume(60);
	klikniecieBuffer.loadFromFile("dzwieki/klik.wav");
	kliknieciePodsumowanieBuffer.loadFromFile("dzwieki/klik_podsumowanie.wav");
	przegranaBuffer.loadFromFile("dzwieki/przegrana.wav");
	wygranaBuffer.loadFromFile("dzwieki/wygrana.wav");
	dzwiekKlikniecie.setBuffer(klikniecieBuffer);
	dzwiekPodsumowanie.setBuffer(kliknieciePodsumowanieBuffer);
	dzwiekPrzegrana.setBuffer(przegranaBuffer);
	dzwiekWygrana.setBuffer(wygranaBuffer);

	////////////DODATKOWE ZMIENNE I USTAWIENIA GRY////////////////////
	unsigned int status_gry = 0; // 0 => menu , 1 => zainicjuj zmienne, 2 => gra , 3 => okno koniec
	unsigned int proba = 0; //Aktualna proba zgadniecia kulki
	unsigned int wynik_wydarzenia = 0; //Czy klikniêto przycisk zmiany koloru, czy klikniêto podsumowanie (potrzebne do efektów dŸwiêkowych)
	sf::Event event;
	sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
	sf::RenderWindow window(desktop, "My window", sf::Style::Fullscreen);//Tworzenie obiektu dla okna
	window.setFramerateLimit(60); //Ustawiamy limit klatek na 60 ¿eby ograniczyæ zu¿ycie GPU
	muzyka.play();

	//////////FUNKCJA G£ÓWNA GRY////////////////////
	while (window.isOpen()){
		window.display();
		window.clear(sf::Color(0, 0, 30));
		window.draw(panel); // Panel na ca³oœæ ekranu (zawiera ekran koncowy, menu)
		
		//================================================//
		//=============Wybór poziomu trudnosci============//
		//================================================//
		if (status_gry == 0) {
			//Ustawiamy baner menu na ca³y ekran
			panel.setScale(sf::Vector2f((float)sf::VideoMode().getDesktopMode().width / (float)teksturaMenu.getSize().x, (float)sf::VideoMode().getDesktopMode().height / (float)teksturaMenu.getSize().y));
			panel.setTexture(teksturaMenu);
			
			window.draw(przyciskTrybLatwy.ZwrocKsztalt());
			window.draw(przyciskTrybTrudny.ZwrocKsztalt());
			window.draw(przyciskWyjdz.ZwrocKsztalt());


			while (window.pollEvent(event))
			{
				//Obs³uga zamykania okna
				if (event.type == sf::Event::Closed)
					window.close();

				if (Kliknieto(przyciskTrybLatwy, window, event)) {
					dzwiekKlikniecie.play();
					ustawLiczba_kulek(4,9);
					WyczyscDane(); //Zmien rozmiar tablic dynamicznych
					status_gry = 1;
				}

				if (Kliknieto(przyciskTrybTrudny, window, event)) {
					dzwiekKlikniecie.play();
					ustawLiczba_kulek(6, 9);
					WyczyscDane(); //Zmien rozmiar tablic dynamicznych
					status_gry = 1;
				}
				if (Kliknieto(przyciskWyjdz, window, event)) {
					dzwiekKlikniecie.play();
					window.close();
				}

				if (Najechano(przyciskTrybLatwy, window))
					przyciskTrybLatwy.UstawObramowanie(7, sf::Color::Red);
				else
					przyciskTrybLatwy.UstawObramowanie(5, sf::Color::White);

				if (Najechano(przyciskTrybTrudny, window))
					przyciskTrybTrudny.UstawObramowanie(7, sf::Color::Red);
				else
					przyciskTrybTrudny.UstawObramowanie(5, sf::Color::White);

				if (Najechano(przyciskWyjdz, window))
					przyciskWyjdz.UstawObramowanie(7, sf::Color::Red);
				else
					przyciskWyjdz.UstawObramowanie(5, sf::Color::White);
			}
		}
		//================================================//
		//=======Tworzenie obiektów kulek, przyciskow=====//
		//================================================//
		if (status_gry == 1){
			//Funkcje przygotowuj¹ce grê // 
			muzyka.stop();
			muzyka.openFromFile("dzwieki/Landing_Godmode.mp3");
			muzyka.play();
			listaKulekTypowana.WyczyscListe();
			listaKulekWylosowana.WyczyscListe();
			listaProstokatow.WyczyscListe();
			listaPodsumowan.WyczyscListe();
			listaWynikow.WyczyscListe();
			listaProstokatowPoprawna.WyczyscListe();
			srand(time(0));
			InicjacjaKulek();
			GenerowanieKulek(listaKulekWylosowana, listaKulekTypowana);
			TworzenieList(listaProstokatow, listaPodsumowan, listaWynikow);
			AktywacjaPrzyciskow(listaProstokatow, listaPodsumowan);
			panel.setScale(0, 0);
			status_gry = 2; //rozpoczynamy grê
			//cout << listaProstokatow.IloscProstokatow();
		}
		//================================================//
		//======Rysowanie obiektów, obs³uga klikniêæ======//
		//================================================//
		if (status_gry == 2) {
			//Rysowanie przyciskow zmiany kulek
			for (int i = 0; i < listaProstokatow.IloscProstokatow(); i++) {
				aktualnie_drukowany = listaProstokatow.ZwrocProstokat(i).ZwrocKsztalt();
				if (i % 3 == 0) {aktualnie_drukowany.setTexture(&teksturaStrzalkaLewo);}
				if (i % 3 == 1) {aktualnie_drukowany.setTexture(&teksturaStrzalkaPrawo);}
				teksturaKulka.setSmooth(true);
				if (i % 3 == 2) {aktualnie_drukowany.setTexture(&teksturaKulka);}
				window.draw(aktualnie_drukowany);
			}
			//Rysowanie przyciskow submit
			for (int i = 0; i < listaPodsumowan.IloscProstokatow(); i++) {
				aktualnie_drukowany = listaPodsumowan.ZwrocProstokat(i).ZwrocKsztalt();
				aktualnie_drukowany.setTexture(&teksturaPodsumowanie);
				window.draw(aktualnie_drukowany);
			}
			//Rysowanie przyciskow wynik
			for (int i = 0; i < listaWynikow.IloscProstokatow(); i++) {
				window.draw(listaWynikow.ZwrocProstokat(i).ZwrocKsztalt());
			}
			aktualnie_drukowany = wyjscieZGry.ZwrocKsztalt();
			aktualnie_drukowany.setTexture(&teksturaZamknij);
			window.draw(aktualnie_drukowany);
			//Generowanie obrazu i obs³uga zdarzeñ
			while (window.pollEvent(event)) {
				//Obs³uga zamykania okna
				if (event.type == sf::Event::Closed)
					window.close();
			
				if(Kliknieto(wyjscieZGry,window,event) == true){
					status_gry = 0;
					//listaProstokatow.WyczyscListe();
					//listaPodsumowan.WyczyscListe();
					//listaWynikow.WyczyscListe();
					//listaKulekTypowana.WyczyscListe();
					//listaKulekWylosowana.WyczyscListe();
					//WyczyscDane(); //Zmien rozmiar tablic dynamicznych
					proba = 0;
				}
				//Jezeli skoncz¹ sie próby to ustawiamy kod gry na 3 tak samo je¿eli zostan¹ zgadniête wszystkie kulki
				wynik_wydarzenia = ObslugaWydarzenKlikniecia(window, event, listaProstokatow, listaPodsumowan, listaWynikow, listaKulekTypowana, listaKulekWylosowana, proba, panel, teksturaPrzegrana, teksturaWygrana);
				if (wynik_wydarzenia == 2 || wynik_wydarzenia == 3){	//Return 2 dla wygranej, return 3 dla przegranej
					if (wynik_wydarzenia == 2) { 
						dzwiekWygrana.play(); 
						muzyka.stop();
						muzyka.openFromFile("dzwieki/The_Darkest_Path_Jeremy_Korpas.mp3");
						muzyka.play();;
					} //dzwiek dla wygranej
					if (wynik_wydarzenia == 3) {
						dzwiekPrzegrana.play(); 
						muzyka.stop(); 
						muzyka.openFromFile("dzwieki/Ten_Inch_Spikes_Jeremy_Korpas.mp3");
						muzyka.play();;
					}	//dzwieki dla przegranej
					/*listaProstokatow.WyczyscListe();
					listaPodsumowan.WyczyscListe();
					listaWynikow.WyczyscListe();
					listaKulekTypowana.WyczyscListe();
					listaKulekWylosowana.WyczyscListe();*/
					proba = 0;
					listaProstokatowPoprawna = WyswietlPoprawneKulki(listaKulekWylosowana); // do wyswietlenia jaka kombinacja kulek by³a poprawna
					status_gry = 3;
					break;
				}
				if (wynik_wydarzenia == 1){		dzwiekKlikniecie.play();}	//return 1 dla klikniecia przycisku zmiany Kulki
				if (wynik_wydarzenia == 4){		dzwiekPodsumowanie.play();} //return 4 dla nieskutecznej proby
			}
		}
		//================================================//
		//=========Okno koncowe Wygrana/Przegrana=========//
		//================================================//
		if (status_gry == 3) {
			window.draw(przyciskWyjdzDoMenu.ZwrocKsztalt());
			window.draw(przyciskPonownie.ZwrocKsztalt());

			for (int i = 0; i < listaProstokatowPoprawna.IloscProstokatow(); i++)
			{
				aktualnie_drukowany =  listaProstokatowPoprawna.ZwrocProstokat(i).ZwrocKsztalt();
				aktualnie_drukowany.setTexture(&teksturaKulkaPodsumowanie);
				window.draw(aktualnie_drukowany);
			}

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				
				if (Kliknieto(przyciskPonownie, window, event) == true) {
					dzwiekKlikniecie.play();
					ustawTablice();
					status_gry = 1;
					panel.setScale(0, 0);
					break;
				}

				if(Kliknieto(przyciskWyjdzDoMenu, window, event) == true) {
					dzwiekKlikniecie.play() ;
					status_gry = 0;
					muzyka.stop();
					muzyka.openFromFile("dzwieki/Secret_Job_Godmode.mp3");
					muzyka.play();
				}

				if (Najechano(przyciskPonownie, window))
					przyciskPonownie.UstawObramowanie(7, sf::Color::Red);
				else
					przyciskPonownie.UstawObramowanie(5, sf::Color::White);

				if (Najechano(przyciskWyjdzDoMenu, window))
					przyciskWyjdzDoMenu.UstawObramowanie(7, sf::Color::Red);
				else
					przyciskWyjdzDoMenu.UstawObramowanie(5, sf::Color::White);
			}
		}
	}
	return 0;
}