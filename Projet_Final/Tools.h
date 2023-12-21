#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>

#define MAX_TIMES 3
#define MAX_NAME_LENGTH 5
#define FILENAME "highscores.txt"

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
void addHighscore(char *username, int time)
