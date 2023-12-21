#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#define LIGNES 2
#define COLONNES 6

void afficherMenu();
void executerJeu();
void jeuDesPaires();
void jouerMemory();
void afficherTimer(time_t debutTimer);
void initialiserCartes(char cartes[LIGNES * COLONNES]);
void melangerCartes(char cartes[LIGNES * COLONNES]);
void afficherCarte(int indice, char carte, bool carteVisible, bool estSelectionnee);
void afficherCartes(char cartes[LIGNES * COLONNES], bool cartesVisibles[LIGNES * COLONNES], int carteSelectionnee);
