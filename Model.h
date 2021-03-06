/** @file */

#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <stdio.h>
#include <stdlib.h>

#include "Struktury.h"

/**
Funkcja dodajaca potomka do struktury drzewa.
@param Dziecko Wskaznik na pierwszy element listy potomkow.
@param idx Indeks do dodania.
@param znak Znak do dodania.
*/
void DodajPotomek(lista** Dziecko, indeks idx, char znak);

/**
Funkcja wyszukujaca wsrod potomkow element przechowujacy dany znak.
@param Dziecko Wskaznik na pierwszy element listy potomkow.
@param znak Szukany znak.
@return Wskaznik na potomka przechowujacy dany znak.
*/
lista* ZnajdzPotomka(lista* Dziecko, char znak);

/**
Funkcja szukajaca wierzcholka odpowiadajacego ciagowi znakow alfa. 
@param Rodzic Wskaznik na wierzcholek rodzica.
@param znak Wskaznik na pierwszy element tablicy znakow.
@param pozycja Biezaca pozycja w tablicy znakow.
@param RozmiarNapisu Rozmiar tablicy znakow.
@return Wskaznik na wierzcholek przechowujacy dany znak.
*/
drzewo* Znajdz(drzewo* Rodzic, char* znak, long long int* pozycja, long long int RozmiarNapisu);

/**
Funkcja wykonujaca kompresje pliku algorytmem LZ78.
@param znak Wskaznik na pierwszy element tablicy znakow.
@param RozmiarNapisu Rozmiar tablicy znakow.
@param nazwa_pliku_wyjsciowego Nazwa pliku wyjsciowego.
*/
void Kompresja(char* znak, long long int RozmiarNapisu, char* nazwa_pliku_wyjsciowego);

/**
Funkcja odczytujaca dlugosc slowa ze slownika.
@param idx Wskaznik na pierwszy element tablicy indeksow.
@param pozycja Biezaca pozycja w tablicy indeksow.
@return Rozmiar slowa do wypisania do pliku wyjsciowego.
*/
long long int DlugoscSlowa(indeks* idx, long long int pozycja);

/**
Funkcja odczytujaca slowo ze slownika.
@param idx Wskaznik na pierwszy element tablicy indeksow.
@param znak Wskaznik na pierwszy element tablicy znakow.
@param pozycja Biezaca pozycja w tablicach indeksow i znakow.
@param RozmiarSlowa Rozmiar odczytywanego slowa.
@param slowo Wskaznik na pierwszy element tablicy odczytywanego slowa.
@return Wskaznik na pierwszy element tablicy odczytywanego slowa.
*/
char* CzytajSlowo(indeks* idx, char* znak, long long int pozycja, long long int RozmiarSlowa, char* slowo);

/**
Funkcja wykonujaca dekompresje pliku algorytmem LZ78.
@param idx Wskaznik na pierwszy element tablicy indeksow.
@param znak Wskaznik na pierwszy element tablicy znakow.
@param RozmiarTablic Rozmiar tablic indeksow i znakow.
@param nazwa_pliku_wyjsciowego Nazwa pliku wyjsciowego.
*/
void Dekompresja(indeks* idx, char* znak, long long int RozmiarTablic, char* nazwa_pliku_wyjsciowego);

/**
Funkcja przygotowujaca plik do wczytania.
@param nazwa_pliku_wejsciowego Nazwa pliku wejsciowego.
@param nazwa_pliku_wyjsciowego Nazwa pliku wyjsciowego.
*/
void WczytajPlik(char* nazwa_pliku_wejsciowego, char* nazwa_pliku_wyjsciowego);

/**
Funkcja wczytujaca plik do kompresji.
@param RozmiarPliku Rozmiar pliku.
@param nazwa_pliku_wejsciowego Nazwa pliku wejsciowego.
@param nazwa_pliku_wyjsciowego Nazwa pliku wyjsciowego.
*/
void WczytajKompresja(long long int RozmiarPliku, char* nazwa_pliku_wejsciowego, char* nazwa_pliku_wyjsciowego);

/**
Funkcja wczytujaca plik do dekompresji.
@param RozmiarPliku Rozmiar pliku.
@param nazwa_pliku_wejsciowego Nazwa pliku wejsciowego.
@param nazwa_pliku_wyjsciowego Nazwa pliku wyjsciowego.
*/
void WczytajDekompresja(long long int RozmiarPliku, char* nazwa_pliku_wejsciowego, char* nazwa_pliku_wyjsciowego);

/**
Funkcja usuwajaca strukture slownika.
@param Drzewo Wskaznik na pierwszy element drzewa do usuniecia.
*/
void UsunSlownik(drzewo* Drzewo);

#endif