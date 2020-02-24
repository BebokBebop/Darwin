/** @file  */


#ifndef LISTY_H
#define LISTY_H
#include<fstream>

typedef char T;

/** Struktura do tworzenia listy znakow. */
struct Znak
{
	T wartosc;
	Znak *pNext;
};


/** Populacja - przechowuje liste osobnikow, dane na jej temat oraz zawiera metody do operacji na tej liscie i jej podlistach. */
class Populacja {
private:
	/** Osobnik - struktura przechowujaca wskaznik na poczatek listy znakow, dlugosc tego ciagu znakow oraz wskaznik na nastepnego Osobnika.*/
	struct Osobnik
	{
		int dlugoscChromosomu = 0;
		Znak *pCiagHead;
		Osobnik *pNext;
		/** Konstruktor
		*@param ciag Wskaznik na pierwszy element listy przechowujacej ciag znakow - chromosom.*/
		Osobnik(Znak*ciag, Osobnik *pNext);
		/** Destruktor*/
		~Osobnik();
		/** Konstruktor kopiujacy. */
		Osobnik (const Osobnik & wzor);
		/** Konstruktor przeniesienia.*/
		Osobnik (Osobnik && wzor);
		/** Operator przypisania. */
		Osobnik & operator=( const Osobnik&);
		
                
		
		
		/** Aktualizuje zmienna przechowujaca ilosc znakow (tj. dlugosc) chromosomu.
		*/
		void updateDlugoscChromo();

		/** Redukuje wszystkie ciagi nastepujacych po sobie bialych znakow do pojedynczej 'spacji'
		*/
		void usunNadmiarSpacji();

		/** Wywoluje inne funkcje, zeby sprawdzic dostosowanie chromosomu do warunkow podanych w funkcjach w pliku ZestawFunkcji.cpp
		* @return Liczbowa reprezentacje dostosowania chromosomu (liczba w zakresie <0-1>
		*/
		double dostosowanie();

		/** Wypisuje chromosom do konsoli
		*/
		void tmpWypiszCiag();
	};

	double  granicaWymierania;
	double granicaRozmnazania;
	int ilePokolen;
	int ileParNaPokolenie;
	int dlugosc = 0;
	Osobnik *pListHead;
	int limitPopulacji=0;

public:
     /** @param ilePokolen Ile razy nalezy zasymulowac jedno pokolenie.
	 * @param ilePokolen Ile razy program ma skrzyzowac i przetestowac chromosomy.
	 * @param ileParNaPokolenie Ile par chromosomow program ma krzyzowac podczas jednego pokolenia.
	 * @param granicaWymierania Minimalna wymagana wartosc dostosowania chromosomu, aby nie zostal usuniety.
	 * @param granicaRozmnazania Minimalna wymagana wartosc dostosowania chromosomu, aby go skolonowac.
	 */
	Populacja(int ilePokolen, int ileParNaPokolenie, 
	      double granicaWymierania, double granicaRozmnazania);
	/**Destruktor*/
	~Populacja();
	/** Konstruktor kopiujacy. */
	Populacja(const Populacja *&kopia);
	/** Konstruktor przeniesienia.*/
	Populacja(Populacja &&wzor);
	/** Operator przypisania. */
	Populacja & operator= (const Populacja&);

	/** Zwraca ilosc elementow w liscie Populacji.
	* @return Dlugosc listy.
	*/
	int size();
	/** Dodaje do listy nowego osobnika.
	* @param ciag Glowa listy przechowujacej chromosom.
	*/
	void dodaj(Znak *ciag);
	/** Usuwa osobnika z listy Populacji.
	* @param id Ktory wpis z kolei w liscie.
	*/
	bool usunOsobnika(const int id);
	/** Usuwa wszystkie osobniki z listy Populacji.
	*/
	void clear();

private:
	/** Znajduje podane przez kolejnosc w liscie obiekty, przecina kazdy na 2 czesci w przypadkowych miejscach i zamienia je wzajemnie koncowymi czesciami.
	* @param samica Ktory z kolei obiekt z listy nalezy skrzyzowac.
	* @param samiec Ktory z kolei obiekt z listy nalezy skrzyzowac.
	*/
	void skrzyzujChromo(int samica, int samiec);
	/** Sprawdza dostosowanie chromosomu kazdego Osobnika po czym decyduje, czy go usunac (jesli dostosowanie jest ponizej progu dostosowania), czy sklonowac.
	*(jesli dostosowanie jest powyzej progu rozmnazania), czy nic z nim nie zrobic (jesli dostosowanie jest pomiedzy granicami wymierania i rozmnazania).
	*/
	void testPopulacji();

	/** Tworzy kopie listy Osobnikow (nowe obiekty).
	* @param oryginal Wskaznik na glowe oryginalnej listy.
	* @return wskaznik Na glowe nowo stworzonej listy-kopii.
	*/
	Osobnik* cpyOsobList(Osobnik* oryginal);

public:
	/** Ustawia maksymalna liczbe osobnikow w populacji.
	* @param nowyMax Nowy limit Populacji.
	*/
	void ustawMax(const int nowyMax);
	
	/** Wywoluje krzyzowanie chromosomow i testowanie populacji podana ilosc razy (generuje nowe pokolenia).
	* @param ilePokolen Ile razy ma powtorzyc tworzenie nowej generacji.
	* @param ileParNaPokolenie Ile par chromosomow ma krzyzowac w jedym pokoleniu.
	* @param granicaWymierania Minimalna wymagana wartosc dostosowania chromosomu, aby nie zostal usuniety.
	* @param granicaRozmnazania Minimalna wymagana wartosc dostosowania chromosomu, aby go skolonowac.
	* @return Jesli wygeneruje zadana ilosc pokolen zwroci true, jesli skonczy przedwczesnie (populacja wymarla, albo nie moze sie juz mnozyc) zwraca false.
	*/
	bool krokPokolenie(int ilePokolen = -1, int ileParNaPokolenie = -1, double granicaWymierania = -1, double granicaRozmnazania = -1);

	/** Wypisuje chromosomy wszystich Osobnikow z listy Populacji.
	*/
	void tmpWypisz();
	
	/** Testuje czy kazdy Osobnik posiada osobny chromosom (czy nie wskazuja na ta sama liste).
	* @return Wartosc true jesli znajdzie 2 rozne Osobniki wskazujace na ta sama liste z chromosomem lub wartosc false jesli takiej pary nie znalazl.
	*/
	bool testOsobnoscList();

	/** Wczytuje chromosomy z pliku do listy Populacji.
	* @param plik Plik z ktorego nalezy wczytac chromosomy.
	*/
	void wczytajListeZPliku(std::ifstream &plik);

	/** Wpisuje zawartosc listy do pliku.
	* @param plik Plik do ktorego nalezy wpisac chromosmy wszystkich Osobnikow z listy Populacji.
	*/
	void wpiszListeDoPliku(std::ofstream &plik);

	/** Usuwa osobniki z listy az jej dlugosc spadnie do podanej w argumencie wartosci.
	* @param doIlu Zadana ilosc Osobnikow w Populacji.
	*/
	void przetrzeb(int doIlu);
};

/** Tworzy kopie listy znakow (nowe obiekty).
* @param oryginal Wskaznik na glowe oryginalnej listy.
* @return Wskaznik na glowe nowo stworzonej listy-kopii.
*/
Znak* cpyCiag(Znak* oryginal);

/** Losuje liczbe naturalna z podanego zakresu, ktora jednoczesnie nie bedzie liczba podana w argumencie blacklist.
* @param zakres Zakres, do ktorego od 0 funkcja ma losowac liczbe.
* @param blacklist Liczba, ktorej funkcja ma nie zwracac (domyslnie -1, bo funkcja zwraca tylko liczby dodatnie).
* @return Liczba z zakresu od 0 do liczby podanej w argumencie zakres, ktora jednoczesnie nie jest liczba podana w argumencie blacklist.
*/
int losujInt(const int zakres, const int blacklist = -1);

/** Funkcja wypisujaca w konsoli podana liczbe oraz reprezentacje graficzna w formie paska ("50[====>     ]" znaczy 50/100).
* @param procent Jaki procent ma wyswietlic.
*/
void wyswietlProcent(int procent);

#endif
