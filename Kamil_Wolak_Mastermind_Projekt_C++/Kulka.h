#pragma once
#include <string>
using namespace std;

class Kulka
{
	private:
		int kodKoloru;
		string kolor;

	public:
		string ZwrocKolor()const;
		const int ZwrocKodKoloru()const; // int kod koloru poniewa¿ kodKoloru = -1 dla braku koloru
		void UstawKolor();
		void UstawKodKoloru(int kodKoloru);
		void UstawKodKoloru(); // je¿eli kod Koloru nie podano parametru wtedy element pusty (do tworzenia pustej listy pocz¹tkowej)
};

