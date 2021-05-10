/** @file */

#include <stdio.h>
#include <stdlib.h>

#include "Widok.h"
#include "Model.h"

void menu(long long int RozmiarPliku, char* nazwa_pliku_wejsciowego, char* nazwa_pliku_wyjsciowego)
{
    int wybor, wynik;
    printf("Wybierz opcje:\n1. Kompresja\n2. Dekompresja\nWybieram: ");
    wynik = scanf("%d", &wybor);

    switch (wybor)
    {
        case 1:
        {
            WczytajKompresja(RozmiarPliku, nazwa_pliku_wejsciowego, nazwa_pliku_wyjsciowego);
            break;
        }
        case 2:
        {
            WczytajDekompresja(RozmiarPliku, nazwa_pliku_wejsciowego, nazwa_pliku_wyjsciowego);
            break;
        }
        default:
            Blad(6);
    }
}

void Blad(int RodzajBledu)
{
    switch (RodzajBledu)
    {
        case 1:
        {
            fputs("Niewlasciwe parametry.", stderr);
            break;
        }
        case 2:
        {
            fputs("Nie moge otworzyc pliku!", stderr);
            break;
        }
        case 3:
        {
            fputs("Plik jest pusty.", stderr);
            break;
        }
        case 4:
        {
            fputs("Blad alokacji pamieci.", stderr);
            break;
        }
        case 5:
        {
            fputs("Za maly maksymalny rozmiar typu. Zmien typ indeksu i/lub ustaw sprawdzanie dla innego typu.", stderr);
            break;
        }
        case 6:
        {
            fputs("Wybierz 1 lub 2!", stderr);
            break;
        }
    }
}