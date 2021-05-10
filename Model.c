/** @file */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Model.h"
#include "Widok.h"

void DodajPotomek(lista** Dziecko, indeks idx, char znak)
{
    if (*Dziecko == NULL)
    {
        *Dziecko = (lista*)malloc(sizeof(lista));
        if (*Dziecko == NULL)
            Blad(4);
        else
        {
            (*Dziecko)->Node.idx = idx;
            (*Dziecko)->Node.znak = znak;
            (*Dziecko)->Node.dziecko = NULL;
            (*Dziecko)->pNext = NULL;
        }
    }
    else
    {
        lista* biezacy = *Dziecko;

        while (biezacy->pNext != NULL)
            biezacy = biezacy->pNext;

        biezacy->pNext = (lista*)malloc(sizeof(lista));
        if (biezacy->pNext == NULL)
            Blad(4);
        else
        {
            biezacy->pNext->Node.idx = idx;
            biezacy->pNext->Node.znak = znak;
            biezacy->pNext->Node.dziecko = NULL;
            biezacy->pNext->pNext = NULL;
        }
    }
}

lista* ZnajdzPotomka(lista* Dziecko, char znak)
{
    if (Dziecko != NULL)
    {
        while (Dziecko != NULL && Dziecko->Node.znak != znak)
            Dziecko = Dziecko->pNext;
        if (Dziecko != NULL && Dziecko->Node.znak == znak)
            return Dziecko;
    }
    return NULL;
}

drzewo* Znajdz(drzewo* Rodzic, char* znak, long long int* pozycja, long long int RozmiarNapisu)
{
    lista* Dziecko;
    char character = znak[(*pozycja)];

    //dopóki nie mamy koñca listy dzieci
    while (Rodzic != NULL)
    {
        Dziecko = ZnajdzPotomka(Rodzic->dziecko, character); //Zwraca element zawieraj¹cy szukany znak (jeœli nie ma takiego, zwraca null).

        if ((*pozycja) < RozmiarNapisu - 1 && Dziecko != NULL)
        {
            (*pozycja)++;
            Rodzic = &(Dziecko->Node);
            character = znak[(*pozycja)];
        }
        else
            break;
    }
    return Rodzic;
}

void Kompresja(char* znak, long long int RozmiarNapisu, char* nazwa_pliku_wyjsciowego)
{
    FILE* wyjsciowy = fopen(nazwa_pliku_wyjsciowego, "wb");

    drzewo* Slownik = (drzewo*)malloc(sizeof(drzewo));
    if (Slownik == NULL)
        Blad(4);
    else
    {
        Slownik->idx = 0;
        Slownik->znak = NULL; //Jest niewa¿ny
        Slownik->dziecko = NULL;

        long long int pozycja = 0; //który z kolei znak rozpatrujemy.
        long long int IndeksNowy = 1; //indeks zapisywany w slowniku.

        while (pozycja < RozmiarNapisu)
        {
            drzewo* Rodzic = Znajdz(Slownik, znak, &pozycja, RozmiarNapisu);  //Szukamy, czy mamy ju¿ czêœæ ci¹gu.

            if (pozycja < RozmiarNapisu)
            {
                if (IndeksNowy < UCHAR_MAX) //Sprawdzamy, czy osi¹gniêto maksymalny rozmiar indeksu.
                {
                    fwrite(&(Rodzic->idx), sizeof(indeks), 1, wyjsciowy); //wpisuje indeksy do pliku
                    fwrite(&znak[pozycja], sizeof(char), 1, wyjsciowy); //wpisuje znaki do pliku
                    DodajPotomek(&(Rodzic->dziecko), IndeksNowy, znak[pozycja]);
                    pozycja++;
                    IndeksNowy++;
                }
                else
                {
                    Blad(5);
                    UsunSlownik(Slownik);
                }
            }
            else
                break;
        }
        UsunSlownik(Slownik);
    }
    fclose(wyjsciowy);
}

long long int DlugoscSlowa(indeks* idx, long long int pozycja)
{
    long long int licznik = 1;
    indeks IndeksPoprzedni = idx[pozycja];

    while (IndeksPoprzedni != 0)
    {
        IndeksPoprzedni = idx[IndeksPoprzedni-1];
        licznik++;
    }

    return licznik;
}

char* CzytajSlowo(indeks* idx, char* znak, long long int pozycja, long long int RozmiarSlowa, char* slowo)
{
    indeks IndeksPoprzedni = idx[pozycja];
    long long int pos = RozmiarSlowa - 1;
    slowo[pos] = znak[pozycja];

    while (IndeksPoprzedni != 0)
    {
        pos--;
        slowo[pos] = znak[IndeksPoprzedni-1];
        IndeksPoprzedni = idx[IndeksPoprzedni-1];
    }

    return slowo;
}

void Dekompresja(indeks* idx, char* znak, long long int RozmiarTablic, char* nazwa_pliku_wyjsciowego)
{
    FILE* wyjsciowy = fopen(nazwa_pliku_wyjsciowego, "wb");

    long long int pozycja = 0;
    while (pozycja < RozmiarTablic)
    {
        long long int RozmiarSlowa = DlugoscSlowa(idx, pozycja);
        char* slowo = (char*)malloc(sizeof(char) * RozmiarSlowa);
        slowo = CzytajSlowo(idx, znak, pozycja, RozmiarSlowa, slowo);
        fwrite(slowo, sizeof(char), RozmiarSlowa, wyjsciowy);
        free(slowo);
        pozycja++;
    }

    fclose(wyjsciowy);
}

void WczytajPlik(char* nazwa_pliku_wejsciowego, char* nazwa_pliku_wyjsciowego)
{
    //Otwieranie pliku.
    FILE* plik = fopen(nazwa_pliku_wejsciowego, "rb");
    if (plik == NULL)
        Blad(2);
    else
    {
        //Odczytanie rozmiaru pliku.
        fseek(plik, 0, SEEK_END);
        long long int RozmiarPliku = ftell(plik);
        fseek(plik, 0, 0);

        //Sprawdzanie, czy plik jest pusty.
        if (RozmiarPliku == 0)
            Blad(3);

        fclose(plik);

        menu(RozmiarPliku, nazwa_pliku_wejsciowego, nazwa_pliku_wyjsciowego);
    }
}

void WczytajKompresja(long long int RozmiarPliku, char* nazwa_pliku_wejsciowego, char* nazwa_pliku_wyjsciowego)
{
    //Otwieranie pliku.
    FILE* plik = fopen(nazwa_pliku_wejsciowego, "rb");
    if (plik == NULL)
        Blad(2);
    else
    {
        //Alokacja pamiêci.
        char* napis = (char*)malloc(sizeof(char) * RozmiarPliku);
        if (napis == NULL)
            Blad(4);
        else
        {
            //Kopiowanie zawartoœci pliku do bufora.
            long long int i = 0;
            while (1)
            {
                fread(&napis[i], sizeof(char), 1, plik);
                if (feof(plik))
                    break;
                i++;
            }

            Kompresja(napis, RozmiarPliku, nazwa_pliku_wyjsciowego);

            //Uwolnienie bufora.
            free(napis);

            fclose(plik);
        }
    }
}

void WczytajDekompresja(long long int RozmiarPliku, char* nazwa_pliku_wejsciowego, char* nazwa_pliku_wyjsciowego)
{
    long long int RozmiarTablicy = RozmiarPliku / (sizeof(indeks) + sizeof(char));

    //Otwieranie pliku.
    FILE* plik = fopen(nazwa_pliku_wejsciowego, "rb");
    if (plik == NULL)
        Blad(2);
    else
    {
        //Alokacja pamiêci.
        indeks* idx = (indeks*)malloc(sizeof(indeks) * RozmiarTablicy); //tablica indeksów
        char* znak = (char*)malloc(sizeof(char) * RozmiarTablicy); //tablica znaków
        if (idx == NULL || znak == NULL)
            Blad(4);
        else
        {
            //Kopiowanie zawartoœci pliku do bufora.
            long long int i = 0;
            while (1)
            {
                fread(&idx[i], sizeof(indeks), 1, plik);
                fread(&znak[i], sizeof(char), 1, plik);
                if (feof(plik))
                    break;
                i++;
            }

            Dekompresja(idx, znak, RozmiarTablicy, nazwa_pliku_wyjsciowego);

            //Uwolnienie bufora.
            free(idx);
            free(znak);

            fclose(plik);
        }
    }
}

void UsunSlownik(drzewo* Drzewo)
{
    if (Drzewo != NULL)
    {
        lista* PoprzednieDziecko = NULL;
        while (Drzewo->dziecko)
        {
            UsunSlownik(&(Drzewo->dziecko->Node));
            PoprzednieDziecko = Drzewo->dziecko;
            Drzewo->dziecko = Drzewo->dziecko->pNext;
            free(PoprzednieDziecko);
        }
        free(Drzewo->dziecko);
        UsunSlownik(Drzewo->dziecko);
    }
}