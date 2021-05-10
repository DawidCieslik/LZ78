/** @file */

#ifndef STRUKTURY_H
#define STRUKTURY_H

/**
@var typedef unsigned char indeks
    Typ indeksu slownika.
*/
typedef unsigned char indeks;

/**
@struct node
    Struktura drzewa trie, ktore sluzy jako slownik.
@var node::idx
    Indeks wierzcholka.
@var node::znak
    Znak przechowywany w wierzcholku.
@var node::dziecko
    Wskaznik na pierwszy element listy potomkow.
*/
typedef struct node
{
    indeks idx;
    char znak;
    struct list* dziecko;
} drzewo;

/**
@struct list
    Struktura listy potomkow drzewa trie.
@var list::Node
    Struktura drzewa trie.
@var list::pNext
    Wskaznik na nastepny element listy potomkow.
*/
typedef struct list
{
    struct node Node;
    struct list* pNext;
} lista;

#endif