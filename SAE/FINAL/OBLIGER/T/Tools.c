#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
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

    if (input == 1) {
        jeuDesPaires();
        }
    } while (input != 2);

    endwin();
}

void jeuDesPaires() {
    WINDOW *fenetre = subwin(stdscr, 5, 50, 1, 1);
    box(fenetre, ACS_VLINE, ACS_HLINE);
    mvwprintw(fenetre, 0, 18, "Jeu des paires");
    mvwprintw(fenetre, 2, 2, "Trouver les paires en un minimum de temps :D");

    WINDOW *fenetre2 = subwin(stdscr, 5, 25, 1, 52); // Ajustez la position X pour éviter le chevauchement
    box(fenetre2, ACS_VLINE, ACS_HLINE);
    mvwprintw(fenetre2, 0, 10, "Chrono");
    mvwprintw(fenetre2, 2, 2, "Le temps est :");
    wrefresh(fenetre2);

    WINDOW *Highscore = subwin(stdscr,5,78,19,1);
    box(Highscore, ACS_VLINE, ACS_HLINE);
    mvwprintw(Highscore,0,35,"Highscore");
    wrefresh(Highscore);

    getch();
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
