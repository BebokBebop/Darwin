/** @file  */

#ifndef ZESTAWFUNKCJI_H
#define ZESTAWFUNKCJI_H
#include"Listy.h"

/** Sumuje dostosowanie chromosomu wobec wszystkich funkcji.
* @param pCiagHead Wskaznik na glowe listy elementow typu ciag przechowujacej wszystkie znaki chromosomu.
* @return Liczbe z zakresu <0-1> oznaczajacej dostosowanie chromosomu do podanych w pliku funkcji (gdzie 0 znaczy, ze chromosom w ogole nie jest dostosowany, a 1, ze jest najlepiej dostosowany).
*/
double fitnessSum(const Znak *pCiagHead);

/** Sprawdza dostosowanie chromosomu wgledem odpowiedniej dlugosci ciagu.
* @param pCiagHead Wskaznik na glowe listy elementow typu ciag przechowujacej wszystkie znaki chromosomu.
* @return Liczbe z zakresu <0-1> oznaczajacej dostosowanie chromosomu funkcji (gdzie 0 znaczy, ze chromosom w ogole nie jest dostosowany, a 1, ze jest najlepiej dostosowany).
*/
double fitFunkDlugosc(const Znak *pCiagHead);

/** Sprawdza dostosowanie chromosomu wgledem ilosci posiadanych w sobie znakow '4'.
* @param pCiagHead Wskaznik na glowe listy elementow typu ciag przechowujacej wszystkie znaki chromosomu.
* @return Liczbe z zakresu <0-1> oznaczajacej dostosowanie chromosomu funkcji (gdzie 0 znaczy, ze chromosom w ogole nie jest dostosowany, a 1, ze jest najlepiej dostosowany).
*/
double fitFunkCzworak(const Znak *pCiagHead);

#endif
