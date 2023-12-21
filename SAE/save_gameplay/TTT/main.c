#include <stdio.h>
#include <stdlib.h>
#include "Tools.h"
#include <ncurses.h>
#include <time.h>

#define LIGNES 2
#define COLONNES 6
int main()
{
    curs_set(0);
    noecho();
    executerJeu();
    afficherMenu();
    clear();
    jeuDesPaires();
    jouerMemory();  // Appeler la fonction pour jouer au Memory

    endwin();
}
