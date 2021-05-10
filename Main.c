/** @file */

#include <stdio.h>
#include <stdlib.h>
//#include <crtdbg.h>

#include "Struktury.h"
#include "Widok.h"
#include "Model.h"

int main(int argc, char* argv[])
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	char* nazwa_pliku_wejsciowego = "Blad",
		* nazwa_pliku_wyjsciowego = "Blad";
	for (int i = 1; i < argc; i++)
	{
		char* argument = argv[i];
		if (!strcmp(argument, "-o"))
			nazwa_pliku_wejsciowego = argv[i + 1];
		else if (!strcmp(argument, "-c"))
			nazwa_pliku_wyjsciowego = argv[i + 1];
	}
	if (nazwa_pliku_wejsciowego == "Blad" || nazwa_pliku_wyjsciowego == "Blad")
		Blad(1);

	WczytajPlik(nazwa_pliku_wejsciowego, nazwa_pliku_wyjsciowego);

	return 0;
}