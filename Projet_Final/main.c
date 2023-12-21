#include <stdio.h>
#include <stdlib.h>
#include "Tools.h"
#include <ncurses.h>
#include <string.h>
#include <time.h>

#define MAX_TIMES 3
#define MAX_NAME_LENGTH 5
#define FILENAME "highscores.txt"

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
    /*char username;

    addHighscore(username, timer);*/
    endwin();
}
