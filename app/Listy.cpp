/** @file */


#include <iostream>
#include <fstream>
#include<chrono>
#include<random>
#include <algorithm>
#include "Listy.h"
#include "ZestawFunkcji.h"



//konstruktory i destruktory 
Populacja::Osobnik::Osobnik(Znak*ciag, Osobnik *pNext) : pCiagHead(ciag), pNext(pNext) {
	updateDlugoscChromo();
}

Populacja::Osobnik::Osobnik(const Osobnik &wzor) {
	pCiagHead = cpyCiag(wzor.pCiagHead);
	dlugoscChromosomu = wzor.dlugoscChromosomu;
}

Populacja::Osobnik::Osobnik(Osobnik && wzor)
{
	std::swap(pCiagHead, wzor.pCiagHead);
	dlugoscChromosomu = wzor.dlugoscChromosomu;
}

Populacja::Osobnik& Populacja::Osobnik::operator=(const Osobnik &wzor) {
	if (&wzor == this) {
		return *this;
	}
	dlugoscChromosomu = wzor.dlugoscChromosomu;
	
	Znak *usuwacz;
	while (pCiagHead)
	{
		usuwacz = pCiagHead;
		pCiagHead = pCiagHead->pNext;
		delete usuwacz;
	}

	pCiagHead = cpyCiag(wzor.pCiagHead);
	return *this;
}

Populacja::Osobnik::~Osobnik() { //void clear()
	Znak *usuwacz;
	while (pCiagHead)
	{
		usuwacz = pCiagHead;
		pCiagHead = pCiagHead->pNext;
		delete usuwacz;
	}
}

Populacja::Populacja(int ilePokolen, int ileParNaPokolenie, double granicaWymierania, double granicaRozmnazania)
	:ilePokolen(ilePokolen), ileParNaPokolenie(ileParNaPokolenie), granicaWymierania(granicaWymierania),
	granicaRozmnazania(granicaRozmnazania), pListHead(nullptr), dlugosc(0) {}

Populacja::Populacja(const Populacja *&wzor) {
	pListHead = cpyOsobList(wzor->pListHead);
	granicaWymierania = wzor->granicaWymierania;
	granicaRozmnazania = wzor->granicaRozmnazania;
	ilePokolen = wzor->ilePokolen;
	ileParNaPokolenie = wzor->ileParNaPokolenie;
	dlugosc = wzor->dlugosc;
	limitPopulacji = wzor->limitPopulacji;
}

Populacja::Populacja(Populacja &&wzor) {
	std::swap(pListHead, wzor.pListHead);
	granicaWymierania = wzor.granicaWymierania;
	granicaRozmnazania = wzor.granicaRozmnazania;
	ilePokolen = wzor.ilePokolen;
	ileParNaPokolenie = wzor.ileParNaPokolenie;
	dlugosc = wzor.dlugosc;
	limitPopulacji = wzor.limitPopulacji;
}

Populacja& Populacja::operator=(const Populacja& wzor) {
	if (&wzor == this) {
		return *this;
	}

	granicaWymierania = wzor.granicaWymierania;
	granicaRozmnazania = wzor.granicaRozmnazania;
	ilePokolen = wzor.ilePokolen;
	ileParNaPokolenie = wzor.ileParNaPokolenie;
	dlugosc = wzor.dlugosc;
	limitPopulacji = wzor.limitPopulacji;

	this->clear();
	pListHead = cpyOsobList(wzor.pListHead);
	return *this;
}

Populacja::~Populacja() {
	clear();
}
//end konstruktory i destruktory

void  Populacja::Osobnik::updateDlugoscChromo() {
	dlugoscChromosomu = 0;
	Znak *krokomierz = pCiagHead;
	if (!krokomierz) { //jesli ktos doda nowego osobnika bez chromosomu (nie zdarzy sie, ale lepiej byc bezpiecznym)
		krokomierz = new Znak{ '\0', nullptr };
	}
	while (krokomierz->wartosc != '\0') {
		dlugoscChromosomu++;
		krokomierz = krokomierz->pNext;
	}
}

void Populacja::Osobnik::usunNadmiarSpacji() {
	Znak *szukacz = pCiagHead;
	Znak *pomoc = nullptr;
	while (szukacz) {
		if (szukacz->wartosc == ' ') {
			while (szukacz->pNext->wartosc == ' ') { //usun kazda kolejna spacje poza pierwsza 
				pomoc = szukacz->pNext;
				szukacz->pNext = szukacz->pNext->pNext;
				delete pomoc;
			}
		}
		szukacz = szukacz->pNext;
	}
}

double Populacja::Osobnik::dostosowanie() {
	double zwracana = fitnessSum(pCiagHead); //funkcje z pliku ZestawFunkcji.cpp
	if (zwracana <= 1.0 && zwracana >= 0.0) { //na wypadek, gdyby ktos zle dodal funkcje do pliku z funkcjami dostosowywania
		return zwracana;
	}
	return 0.0;
}

void Populacja::Osobnik::tmpWypiszCiag() {
	Znak *znak = pCiagHead;
	while (znak) {
		std::cout << znak->wartosc;
		znak = znak->pNext;
	}
}

void Populacja::clear() {
	dlugosc = 0;
	Osobnik *usuwacz;
	while (pListHead)
	{
		usuwacz = pListHead;
		pListHead = pListHead->pNext;
		delete usuwacz;
	}
}

int Populacja::size() { return dlugosc; }

void Populacja::dodaj(Znak *ciag) {
	pListHead = new Osobnik(ciag, pListHead);
	dlugosc++;
}

bool Populacja::usunOsobnika(const int id) {
	if (!pListHead) { //lista jest pusta (nie wydarzy sie)
		return false;
	}
	else if (id < 0) { //niewlasciwy indeks obiektu z listy (nie wydarzy sie)
		return false;
	}
	else if (id == 0) { //usun pierwszy 
		Osobnik *usuwacz = pListHead;
		pListHead = pListHead->pNext;
		delete usuwacz;
		dlugosc--;
	}
	else {
		Osobnik *poszukiwacz = pListHead;
		for (int i = 0; i < id - 1; i++) {
			poszukiwacz = poszukiwacz->pNext;

			if (poszukiwacz->pNext == nullptr) { //proba usuniecia obiektu z poza zakresu listy (nie wydarzy sie)
				return false;
			}
		}
		Osobnik *znaleziony = poszukiwacz->pNext;
		poszukiwacz->pNext = poszukiwacz->pNext->pNext;
		delete znaleziony; //destruktor sie wszystkim zajmuje
		znaleziony = nullptr;
		dlugosc--;
	}
	return true;
}

bool Populacja::krokPokolenie(int ilePokolen, int ileParNaPokolenie, double granicaWymierania, double granicaRozmnazania /*w deklaracji wszystkie domyslnie =-1*/) {
	int Osobnik1, Osobnik2;

	if (dlugosc < 2) { //W populacji brakuje osobnikow do mnozenia;
		return false;
	}

	//jesli korzystamy z podanych w argumentach funkcji main wspolczynnikow (mozna wywolac ta funkcje w programie z innymi wartosciami)
	if (ileParNaPokolenie == -1)
		ileParNaPokolenie = this->ileParNaPokolenie;
	if (ilePokolen == -1)
		ilePokolen = this->ilePokolen;
	if (granicaRozmnazania == -1)
		granicaRozmnazania = this->granicaRozmnazania;
	if (granicaWymierania == -1)
		granicaWymierania = this->granicaWymierania;

	for (int i = 0; i < ilePokolen; i++) {
		if (!pListHead || dlugosc < 2) { //brakuje osobnikow
			break;
		}
		for (int j = 0; j < ileParNaPokolenie; j++) { //wylosuj osobniki do krzyzowania
			Osobnik1 = losujInt(dlugosc - 1);
			Osobnik2 = losujInt(dlugosc - 1, Osobnik1);
			skrzyzujChromo(Osobnik1, Osobnik2);
		}
		testPopulacji(); //sprawdz dostosowanie, potem zabij, rozmnoz lub zostaw w spokoju
		if (limitPopulacji<dlugosc) { //sprawdz czy trzeba skrocic liste Osobnikow
			przetrzeb(limitPopulacji);
		}
		wyswietlProcent((int)(i * 100 / ilePokolen)); //zeby zapewnic w konsoli uzytkownika, ze wszystko dziala
	}
	if (dlugosc < 2)
	{
		//W populacji brakuje osobnikow do mnozenia;
		return false;
	}
	wyswietlProcent(100); //finisz
	return true;
}

void Populacja::skrzyzujChromo(int samica, int samiec) {
	if (samiec >= dlugosc || samica >= dlugosc) {
		return; //nie wydarzy sie
	}
	else {
		Osobnik *ona = nullptr, *on = nullptr;
		if (samiec < samica) { //samica musi byc przed samcem
			int tmp = samiec;
			samiec = samica;
			samica = tmp;
		}
		on = pListHead;
		for (int i = 0; i < samiec; i++) { //zeby to dzialalo ^^^
			if (i == samica) {
				ona = on;
			}
			on = on->pNext;
		}

		int pktPrzec1 = losujInt(ona->dlugoscChromosomu); //gdzie je przecinamy
		int pktPrzec2 = losujInt(on->dlugoscChromosomu);

		Znak *jejChrom = ona->pCiagHead;
		Znak *jegoChrom = on->pCiagHead;

		for (int i = 1; i < pktPrzec1; i++) { //przesuwam do miejsca przeciecia
			jejChrom = jejChrom->pNext;
		}
		for (int i = 1; i < pktPrzec2; i++) {
			jegoChrom = jegoChrom->pNext;
		}

		Znak *swapper = jegoChrom->pNext; //zamieniam koncowki list tj. krzyzuje chromosomy
		jegoChrom->pNext = jejChrom->pNext;
		jejChrom->pNext = swapper;
		swapper = nullptr;

		//update chromoosmu i Osobnika co go zawiera
		ona->usunNadmiarSpacji();
		ona->updateDlugoscChromo();
		on->usunNadmiarSpacji();
		on->updateDlugoscChromo();
	}
}

void Populacja::testPopulacji() {
	Osobnik *usuwacz = pListHead;
	double fitness = pListHead->dostosowanie(); //pListHead musi istniec
	
	//sprawdzanie z poczatku listy
	while (pListHead) { 
		if (fitness < granicaWymierania) {
			usuwacz = pListHead;
			pListHead = pListHead->pNext;
			delete usuwacz;
			dlugosc--;
			usuwacz = pListHead;
			if (!pListHead)
				return;
			fitness = pListHead->dostosowanie();
		}
		else if (fitness > granicaRozmnazania) {
			dodaj(cpyCiag(pListHead->pCiagHead));
			break;
		}
		else
			break;
	}

	//sprawdzanie ze srodka listy
	Osobnik *Badacz = pListHead;
	while (Badacz->pNext) { 
		fitness = Badacz->pNext->dostosowanie();
		if (fitness < granicaWymierania) {
			usuwacz = Badacz->pNext;
			Badacz->pNext = Badacz->pNext->pNext;
			delete usuwacz;
			dlugosc--;
		}
		else if (fitness > granicaRozmnazania) {
			dodaj(cpyCiag(Badacz->pNext->pCiagHead));
			Badacz = Badacz->pNext;
		}
		else
			Badacz = Badacz->pNext;
	}
}

void Populacja::tmpWypisz() {
	Osobnik *przesuwacz = pListHead;
	std::cout << "Lista populacji:\n";
	if (!pListHead) {
		std::cout << "<pusto>\n";
	}
	while (przesuwacz) {
		przesuwacz->tmpWypiszCiag();
		std::cout << std::endl;
		przesuwacz = przesuwacz->pNext;
	}
	std::cout << "--- Koniec Listy ---\n";
}

bool Populacja::testOsobnoscList() { //tyko do debugu
	if (!pListHead) {
		return false;
	}
	Osobnik *pomoc1 = pListHead->pNext, *pomoc2 = pListHead;
	for (int i = 0; i < dlugosc - 1; i++) {
		while (pomoc1) {
			if (pomoc1->pCiagHead == pomoc2->pCiagHead)
				return true;
			pomoc1 = pomoc1->pNext;
		}
		pomoc2 = pomoc2->pNext;
		pomoc1 = pomoc2->pNext;
	}
	return false;
}

void Populacja::wczytajListeZPliku(std::ifstream &plik) {
	char znak = 0;
	Znak *pCiagHead = new Znak{ '\0',nullptr }; //pCiagHead wskazuje na pierwszy element
	Znak *ostatniZnak = pCiagHead;
	while (plik.get(znak)) {
		if (znak == '\n') {
			dodaj(pCiagHead);
			pCiagHead = new Znak{ '\0',nullptr };
			ostatniZnak = pCiagHead;
			continue;
		}
		ostatniZnak->wartosc = znak;
		ostatniZnak->pNext = new Znak{ '\0',nullptr };
		ostatniZnak = ostatniZnak->pNext;
	}
	if (pCiagHead->wartosc != '\0') {
		dodaj(pCiagHead);
	}
	else {
		delete pCiagHead; //ciagu z jednym znakiem '\0' nie chce dodawac do listy
	}
}

void Populacja::wpiszListeDoPliku(std::ofstream &plik) {
	Osobnik *przesuwacz = pListHead;
	while (przesuwacz) {
		Znak *znak = przesuwacz->pCiagHead;
		while (znak->wartosc != '\0') {
			plik << znak->wartosc;
			znak = znak->pNext;
		}
		plik << std::endl;
		przesuwacz = przesuwacz->pNext;
	}
}

void Populacja::ustawMax(const int nowyMax) {
	if (!(nowyMax < 0)) {
		limitPopulacji = nowyMax;
	}
}

Populacja::Osobnik* Populacja::cpyOsobList(Osobnik* oryginal) { //przydatne tylko dla konstruktorow 
	if (!oryginal) {
		return nullptr;
	}

	Osobnik *nowyCiagHead, *skladaczCiagu;
	skladaczCiagu = new Osobnik(cpyCiag(oryginal->pCiagHead), nullptr);
	nowyCiagHead = skladaczCiagu;
	oryginal = oryginal->pNext;

	while (oryginal) //skopiowac kazdy element i jego osobna liste
	{
		skladaczCiagu->pNext = new Osobnik(cpyCiag(oryginal->pCiagHead), nullptr);
		skladaczCiagu = skladaczCiagu->pNext;
		oryginal = oryginal->pNext;
	}

	return nowyCiagHead;
}

void Populacja::przetrzeb(int doIlu) {
	while (dlugosc > doIlu) {
		if (!usunOsobnika(losujInt(dlugosc)))
			return;
	}
}

Znak* cpyCiag(Znak* oryginal) { //kopiuje ciag znakow do nowej listy
	if (!oryginal) {
		return nullptr;
	}

	Znak *nowyCiagHead, *skladaczCiagu;
	skladaczCiagu = new Znak{ oryginal->wartosc, nullptr };
	nowyCiagHead = skladaczCiagu;
	oryginal = oryginal->pNext;

	while (oryginal)
	{
		skladaczCiagu->pNext = new Znak{ oryginal->wartosc, nullptr };
		skladaczCiagu = skladaczCiagu->pNext;
		oryginal = oryginal->pNext;
	}

	return nowyCiagHead;
}

int losujInt(const int zakres, const int blacklist /*=-1 w deklaracji*/) {
	auto czas = std::chrono::system_clock::now();
	auto interwal = czas.time_since_epoch();
	std::default_random_engine silnik;
	std::uniform_int_distribution<int> rozklad(0, zakres);
	silnik.seed(interwal.count());

	int wylosowana = blacklist;

	while (wylosowana == blacklist)
		wylosowana = rozklad(silnik);

	return wylosowana;
}

void wyswietlProcent(int procent) { // x[===..x..=>   ]
	std::cout.flush();
	if (procent < 10) {
		std::cout << "\r " << procent << "[";
	}
	else {
		std::cout << '\r' << procent << "[";
	}

	for (int i = 0; i < procent - 1; i++) {
		std::cout << "=";
	}
	std::cout << ">";
	for (int i = procent; i < 100; i++) {
		std::cout << " ";
	}
	std::cout << "] ";
	if (procent == 100) {
		std::cout << '\n';
	}
}
