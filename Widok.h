/** @file */

#ifndef WIDOK_H
#define WIDOK_H

#include <stdio.h>
#include <stdlib.h>

#include "Struktury.h"

/**
Funkcja umozliwiajaca wybor miedzy kompresja a dekompresja.
@param RozmiarPliku Rozmiar pliku.
@param nazwa_pliku_wejsciowego Nazwa pliku wejsciowego.
@param nazwa_pliku_wyjsciowego Nazwa pliku wyjsciowego.
*/
void menu(long long int RozmiarPliku, char* nazwa_pliku_wejsciowego, char* nazwa_pliku_wyjsciowego);

/**
Funkcja wyswietlajaca komunikat o bledzie.
@param RodzajBledu 1 - blad parametrow; 2 - blad otwarcia pliku; 3 - pusty plik; 4 - blad alokacji pamieci; 5 - za maly maksymalny rozmiar indeksu; 6 - blad wyboru.
*/
void Blad(int RodzajBledu);


#endif