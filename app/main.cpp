/** @file */

#include <fstream>
#include<iostream>
#include"Listy.h"
#include"TestArgumentow.h"

//-i populacja.txt -o output.txt -r 0.75 -w 0.5 -k 15 -p 100   <-dziala

int main(int argc, char **argv)
{
	std::ifstream plikWejsciowy;
	std::ofstream plikWyjsciowy;
	double granicaWymierania, granicaRozmnazania;
	int ileParNaPokolenie, ilePokolen;

	std::string Bledy = check_param(argc, argv, plikWejsciowy, plikWyjsciowy, granicaWymierania, granicaRozmnazania, ileParNaPokolenie, ilePokolen);
	
	//jesli jakies bledy zostaly zwrocone, to je wyswietla i konczy program
	if (Bledy.size()) {
		std::cout << Bledy;
		return 0;
	}

	//glowny obiekt z lista osobnikow
	Populacja glowa(ilePokolen, ileParNaPokolenie, granicaWymierania, granicaRozmnazania);

	glowa.wczytajListeZPliku(plikWejsciowy);
	plikWejsciowy.close();

	//bez obaw, ze plik tekstowy mi zje komputer
	int maksymalnaIloscOsobnikow = 500;
	glowa.ustawMax(maksymalnaIloscOsobnikow);

	//wlaczam generowanie populacji i sprawdzam, czy sie przedwczesnie nie skoczylo
	if (!glowa.krokPokolenie()) {
		std::cout << "\nPopulacja nie moze sie juz mnozyc\n";
	}

	//jesli chce zobaczyc w konsoli
	//glowa.tmpWypisz();
	//std::cout << "Wielkosc Populacji: " << glowa.size() << '\n';

	glowa.wpiszListeDoPliku(plikWyjsciowy);
	plikWyjsciowy.close();

	return 0;
}

