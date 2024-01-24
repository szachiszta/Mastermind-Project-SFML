#pragma once
#include "Prostokat.h"
#include "ListaProstokatow.h"
#include "ListaKulek.h"
#include <SFML/Graphics.hpp>

unsigned int ObslugaWydarzenKlikniecia(sf::RenderWindow& window, sf::Event& event, ListaProstokatow& listaProstokatow, ListaProstokatow& listaPodsumowan,
	                          ListaProstokatow& listaWynikow, ListaKulek& listaKulekTypowana, ListaKulek& listaKulekWylosowana, unsigned int& proba, 
	                          sf::Sprite& panel, sf::Texture& teksturaPrzegrana, sf::Texture& teksturaWygrana);
bool Kliknieto(Prostokat prostokat, sf::RenderWindow& window, sf::Event& event);
bool Najechano(Prostokat prostokat, sf::RenderWindow& window);
void GenerowanieKulek(ListaKulek& listaKulekWylosowana, ListaKulek& listaKulekTypowana);
void AktywacjaPrzyciskow(ListaProstokatow& listaProstokatow, ListaProstokatow& listaPodsumowan); //Dla wstepnego wyzerowania
void AktywacjaPrzyciskow(ListaProstokatow& listaProstokatow, ListaProstokatow& listaPodsumowan, unsigned int& proba);
void ZmienKodKulki(int indeks, ListaProstokatow& listaprostokatow);
void InicjacjaKulek();
bool PodsumowanieProby(ListaKulek& listaKulek, ListaKulek& listaKulekWylosowana, unsigned int& proba, ListaProstokatow& listaProstokatow, ListaProstokatow& listaPodsumowan);
void UstawWyniki(unsigned int& proba, ListaProstokatow& listawynikow);
void ustawTablice();
void mieszanieTablicy(int arr[], int n);
void TworzenieList(ListaProstokatow& listaProstokatow, ListaProstokatow& listaPodsumowan, ListaProstokatow& listaWynikow);
void ustawLiczba_kulek(const unsigned int liczba_kulekUstaw, const unsigned int liczba_probUstaw);
ListaProstokatow WyswietlPoprawneKulki(ListaKulek& listaKulekWylosowana);
void WyczyscDane();