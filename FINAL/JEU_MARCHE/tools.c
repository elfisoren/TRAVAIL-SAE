
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


#define LIGNES 2
#define COLONNES 6

int input;
void executerJeu() {
    WINDOW *fenetre;
    initscr();
    curs_set(TRUE);

    fenetre = subwin(stdscr, 0, 0, 0, 0);
    box(fenetre, ACS_VLINE, ACS_HLINE);

    mvwprintw(fenetre, 1, 4, "-------------------------------------------------------------------------");
    mvwprintw(fenetre, 2, 4, "    * **** *   *   ***   ****   **    ***     *      *   ****   ****   **");
    mvwprintw(fenetre, 3, 4, "    * *    *   *   *  *  *     *      *  *   * *     *   *  *   *     *  ");
    mvwprintw(fenetre, 4, 4, "    * **   *   *   *  *  **     *     * *   *****    *   * *    **     * ");
    mvwprintw(fenetre, 5, 4, " *  * *    *   *   *  *  *       *    *    *     *   *   *  *   *        *");
    mvwprintw(fenetre, 6, 4, "  **  ****  ***    ***   ****  **     *   *       *  *   *   *  ****  ** ");
    mvwprintw(fenetre, 7, 4, "-------------------------------------------------------------------------");


    // affichage menu avec l'option 1 et 2
    do {
        afficherMenu();
        // Appeler la fonction jeuDesPaires si l'option 1 est choisie
            if (input == 1) {
            curs_set(FALSE);
            clear();  // Effacer tout le contenu affiché
            wrefresh(fenetre);  // Mettre à jour l'affichage
            jeuDesPaires();
            wclear(fenetre);  // Effacer le contenu de la fenêtre principale
            box(fenetre, ACS_VLINE, ACS_HLINE);  // Redessiner la bordure de la fenêtre principale
            wrefresh(fenetre);  // Mettre à jour l'affichage de la fenêtre principale
        }
    } while (input != 2);

    endwin();
}

void jeuDesPaires() {
    // Créer la première fenêtre
    WINDOW *fenetre = subwin(stdscr, 5, 50, 1, 1);
    box(fenetre, ACS_VLINE, ACS_HLINE);
    mvwprintw(fenetre, 0, 18, "Jeu des paires");
    mvwprintw(fenetre, 2, 2, "Trouver les paires en un minimum de temps :D");
    wrefresh(fenetre);

    // Créer la deuxième fenêtre
    WINDOW *fenetre2 = subwin(stdscr, 5, 25, 1, 52); // Ajustez la position X pour éviter le chevauchement
    box(fenetre2, ACS_VLINE, ACS_HLINE);
    mvwprintw(fenetre2, 0, 5, "Chrono");  // Ajustez la position X pour centrer le texte
    mvwprintw(fenetre2, 2, 2, "Le temps est :");
    wrefresh(fenetre2);

    // Créer la troisième fenêtre
    WINDOW *Highscore = subwin(stdscr, 8, 78, 16, 1);
    box(Highscore, ACS_VLINE, ACS_HLINE);
    mvwprintw(Highscore, 0, 35, "Highscore");  // Ajustez la position X pour centrer le texte
    wrefresh(Highscore);

    getch();

    // Supprimer les fenêtres
    delwin(fenetre);
    delwin(fenetre2);
    delwin(Highscore);
}



void afficherMenu() {
    WINDOW *fenetre;
    int y, x;
    initscr();
    curs_set(TRUE);

    fenetre = subwin(stdscr, 0, 0, 0, 0);
    box(fenetre, ACS_VLINE, ACS_HLINE);

    // affichage menu avec l'option 1 et 2
    mvwprintw(fenetre, 15, 2, "MENU\n");
    mvwprintw(fenetre, 16, 2, "1. 1 Joueur\n");
    mvwprintw(fenetre, 17, 2, "2. Autoplayer\n");
    mvwprintw(fenetre, 18, 2, "Entrer votre choix : ");
    getyx(fenetre, y, x);
    mvwscanw(fenetre, y, x, "%d", &input);

    // Vérifier si l'entrée est valide (1 ou 2)
    while (input != 1 && input != 2) {
        mvwprintw(fenetre, y + 1, 2, "Choix invalide. Veuillez entrer 1 ou 2.");
        wclrtoeol(fenetre); // Effacer la ligne de la fenêtre
        wmove(fenetre, y, x); // Se déplacer à la position du curseur
        int i;
        for (i = 0; i < COLS - x; i++) {
            wdelch(fenetre);
        }
        wrefresh(fenetre);
        mvwprintw(fenetre, 18, 2, "Entrer votre choix : ");
        mvwscanw(fenetre, y, x, "%d", &input);
    }

    wrefresh(fenetre);
}

void initialiserCartes(char cartes[LIGNES * COLONNES]) {
    char valeurCarte = 'A';

    for (int i = 0; i < LIGNES * COLONNES; ++i) {
        cartes[i] = valeurCarte;
        valeurCarte++;
        if (valeurCarte > 'F') {
            valeurCarte = 'A';
        }
    }
}

void melangerCartes(char cartes[LIGNES * COLONNES]) {
    srand(time(NULL));

    for (int i = 0; i < LIGNES * COLONNES; ++i) {
        int temp = rand() % (LIGNES * COLONNES);

        // Échanger les positions des cartes
        char tempCarte = cartes[i];
        cartes[i] = cartes[temp];
        cartes[temp] = tempCarte;
    }
}

void afficherCarte(int indice, char carte, bool carteVisible, bool estSelectionnee) {
    if (estSelectionnee) {
        //attron(A_REVERSE); // Activer l'inversion des couleurs
        attron(COLOR_PAIR(1)); // Rouge pour la sélection
    } else if (carteVisible) {
        //attron(COLOR_PAIR(2)); // Vert pour les cartes retournées
    }

    mvprintw(indice / COLONNES * 4, (indice % COLONNES) * 8, " #-----#");
    mvprintw(indice / COLONNES * 4 + 1, (indice % COLONNES) * 8, " #     #");
    mvprintw(indice / COLONNES * 4 + 2, (indice % COLONNES) * 8, " #  %c  #", carteVisible ? carte : ' ');
    mvprintw(indice / COLONNES * 4 + 3, (indice % COLONNES) * 8, " #-----#");


    if (estSelectionnee || carteVisible) {
        attroff(COLOR_PAIR(1));
        //attroff(COLOR_PAIR(2));
        //attroff(A_REVERSE);
    }
}








