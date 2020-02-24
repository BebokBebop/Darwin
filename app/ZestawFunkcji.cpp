/** @file */

#include"ZestawFunkcji.h"
#include"Listy.h"
#include<chrono>
#include<random>


double fitnessSum(const Znak *pCiagHead) {
	double sumaWartosci = 0;
	sumaWartosci += fitFunkDlugosc(pCiagHead)/2; 
	sumaWartosci += fitFunkCzworak(pCiagHead)/2;
	if (sumaWartosci > 1 || sumaWartosci < 0) {
		return 0;
	}
	return sumaWartosci; //trzeba pilnowac, zeby nie zwrocic wartosci wiekszej niz 1!
}

double fitFunkCzworak(const Znak *pCiagHead) { //im wiecej '4' tym lepiej
	int ileCzworek = 1;
	while (pCiagHead->wartosc!='\0') {
		if (pCiagHead->wartosc == '4') {
			ileCzworek++;
		}
		pCiagHead = pCiagHead->pNext;
	}
	return 1.0 - 1.0 / ileCzworek;
}

double fitFunkDlugosc(const Znak *pCiagHead) { //im dlugosc ciagu jest blizej podanej 'najlepszejDlugosci' tym wieksza wartosc zwracam
	int najlepszaDlugosc = 23;
	int dlugoscCiagu = 0;
	int jakBliskoDoNajlepszejDlugosci = 0;
	double wartoscZwracana = 0;

	if (!pCiagHead) {
		return 0;
	}
	while (pCiagHead) {
		dlugoscCiagu++;
		pCiagHead = pCiagHead->pNext;
	}
	dlugoscCiagu--; //na koncu ciagu jest '\0'

	jakBliskoDoNajlepszejDlugosci = dlugoscCiagu - najlepszaDlugosc;

	if (jakBliskoDoNajlepszejDlugosci < 0) { //wartosc bezwzgledna
		jakBliskoDoNajlepszejDlugosci *= -1.0;
	}

	wartoscZwracana = -0.07 * jakBliskoDoNajlepszejDlugosci + 1; //optymalna funkcja liniowa
	if (wartoscZwracana < 0) {
		return 0;
	}

	return wartoscZwracana;
}
