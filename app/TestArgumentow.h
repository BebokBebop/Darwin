/** @file  */

#ifndef TESTARGUMENTOW_H
#define TESTARGUMENTOW_H
#include<string>

/** Zamienia ciag znakow z przecinkiem na liczbe zmiennoprzecinkowa.
* @param tablica Ciag znakow.
* @return Liczbe odczytana z ciagu znakow przekazanego w argumencie lub -1 gdy ciag znakow nie jest liczba zmiennoprzecinkowa.
*/
double doLiczby(char*tablica);

/** Sprawdza poprawnosc podanych do funkcji main argumentow i zwraca komunikaty ewentualnych bledow.
 * @param argc Ilosc argumentow przekazanych do funkcji main (tj. wraz z wywolaniem programu).
 * @param argv Dwuwymiarowa tablica przechowujaca argumenty przekazane do funkcji main (tj. wraz z wywolaniem programu).
 * @param[out] plikWejsciowy Obiekt typu ofstream. W funkcji probuje otworzyc nim plik.
 * @param[out] plikWyjsciowy Obiekt typu ofstream. W funkcji zostaje mu otwarty strumien.
 * @param[out] granicaWymierania Minimalna wymagana wartosc dostosowania chromosomu, aby nie zostal usuniety.
 * @param[out] granicaRozmnazania Minimalna wymagana wartosc dostosowania chromosomu, aby go skolonowac.
 * @param[out] ileParNaPokolenie Ile par chromosomow program ma krzyzowac podczas jednego pokolenia.
 * @param[out] ilePokolen Ile razy program ma skrzyzowac i przetestowac chromosomy.
 * @return Ciag znakow zawierajacy wykryte w funkcji bledy w argumentach lub ciag pusty, jesli zadnych bledow nie bylo.
 */ 
std::string check_param(int argc, char **argv, std::ifstream &plikWejsciowy, std::ofstream &plikWyjsciowy, 
	double &granicaWymierania, double &granicaRozmnazania, int &ileParNaPokolenie, int &ilePokolen);

#endif
