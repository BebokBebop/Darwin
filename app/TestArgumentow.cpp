/** @file */

#include"TestArgumentow.h"
#include<string>
#include<string.h>
#include<fstream>


double doLiczby(char *tablica) {
	double zwracanaWartosc = 0.0;
	while (*tablica >= '0' && *tablica <= '9') {
		zwracanaWartosc = (zwracanaWartosc*10.0) + (*tablica - '0');
		++tablica;
	}
	if (*tablica == '.' || *tablica == ',') {
		int poPrzecinku = 1;
		++tablica;
		while (*tablica >= '0' && *tablica <= '9') {
			zwracanaWartosc = (zwracanaWartosc*10.0) + (*tablica - '0');
			poPrzecinku *= 10;
			++tablica;
		}
		if (*tablica != '\0') {
			return -1;
		}
		zwracanaWartosc /= poPrzecinku;
	}
	else if(*tablica!='\0')
		return -1;
	return zwracanaWartosc;
}

std::string check_param(int argc, char **argv, std::ifstream &plikWejsciowy, std::ofstream &plikWyjsciowy, 
	double &granicaWymierania, double &granicaRozmnazania, int &ileParNaPokolenie, int &ilePokolen) {
	std::string badUse = "Zle uzycie.\nWpisz: \"" + (std::string)argv[0] + " -h\"\nlub \"" + (std::string)argv[0] + " help\",\nzeby otrzymac pomoc.\n";

	std::string help = "Wpisz \"" + (std::string)argv[0] + " -i [nazwa_pliku_wejsciowego] \n-o [nazwa_pliku_wyjsciowego]\n"
		+ "-r [granica romnazania <0-1>] \n-w [granica wymierania <0-1>] \n-k [ile par na pokolenie] \n-p [ile pokolen]\" \n";
	
	std::string errorZwrot = "";
	std::string przelaczniki[6] = { "i","o","r","w","k","p" };
	int wymaganePrzelaczniki[6] = { 0 };
	int zleWartosci[6] = { 0 };

	std::string input, output;

	if (argc == 1)
		return badUse;
	for (int i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "-i")) {
			wymaganePrzelaczniki[0]++;
			if (++i >= argc) {
				return badUse;
			}
			else
				input = argv[i];
		}

		else if (!strcmp(argv[i], "-o")) {
			wymaganePrzelaczniki[1]++;
			if (++i >= argc) {
				return badUse;
			}
			else
				output = argv[i];
		}
		else if (!strcmp(argv[i], "-r")) {
			wymaganePrzelaczniki[2]++;
			if (++i >= argc) {
				return badUse;
			}
			else {
				granicaRozmnazania = doLiczby(argv[i]);
				if (granicaRozmnazania == -1) {
					zleWartosci[2] = 1;
				}
				else if (granicaRozmnazania > 1 || granicaRozmnazania < 0)
					zleWartosci[2] = 2;
			}
		}
		else if (!strcmp(argv[i], "-w")) {
			wymaganePrzelaczniki[3]++;
			if (++i >= argc) {
				return badUse;
			}
			else {
				granicaWymierania = doLiczby(argv[i]);
				if (granicaWymierania == -1) {
					zleWartosci[3] = 1;
				}
				else if (granicaWymierania > 1 || granicaWymierania < 0)
					zleWartosci[3] = 2;
			}
		}
		else if (!strcmp(argv[i], "-k")) {
			wymaganePrzelaczniki[4]++;
			if (++i >= argc) {
				return badUse;
			}
			else {
				ileParNaPokolenie = doLiczby(argv[i]);
				if (ileParNaPokolenie == -1) {
					zleWartosci[4] = 1;
				}
			}
		}
		else if (!strcmp(argv[i], "-p")) {
			wymaganePrzelaczniki[5]++;
			if (++i >= argc) {
				return badUse;
			}
			else {
				ilePokolen = doLiczby(argv[i]);
				if (ilePokolen == -1) {
					zleWartosci[5] = 1;
				}
			}
		}
		else if (!strcmp(argv[i], "help") || !strcmp(argv[i], "-h")) {
			return help;
		}
		else {
			return badUse;
		}
	}


	for (int i = 0; i < 6; i++) {
		if (wymaganePrzelaczniki[i] > 1) {
			errorZwrot += ">Przelacznik [-" + przelaczniki[i] + "] zostal uzyty wiecej niz raz\n";
		}
		else if (!wymaganePrzelaczniki) {
			errorZwrot += ">Przelacznik [-" + przelaczniki[i] + "] nie zostal uzyty\n";
		}
		else{
			if (zleWartosci[i] == 1) {
				errorZwrot += ">wartosc po \"-" + przelaczniki[i] + "\" nie jest liczba\n";
			}
			else if (zleWartosci[i] == 2) {
				errorZwrot += ">Podane \"-" + przelaczniki[i] + "\" jest poza zakresem <0-1>\n";
			}
		}
	}
	plikWejsciowy.open(input);
	plikWyjsciowy.open(output);

	if(!plikWejsciowy)
	{
		errorZwrot += ">Nie mozna otworzyc pliku wejsciowego\n";
	}

	if (!plikWyjsciowy)
	{
		errorZwrot += ">Nie mozna otworzyc pliku wyjsciowego\n";
	}

	return errorZwrot;
}
