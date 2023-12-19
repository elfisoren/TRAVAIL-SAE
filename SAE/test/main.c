#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int input;

void afficherMenu();

int main(void) {
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
    } while (input != 1 && input != 2);

    clear();
    wrefresh(fenetre);
    getch();
    endwin();

    return 0;
}

void afficherMenu() {
    WINDOW *fenetre;
    initscr();
    curs_set(TRUE);

    fenetre = subwin(stdscr, 0, 0, 0, 0);
    box(fenetre, ACS_VLINE, ACS_HLINE);

    // affichage menu avec l'option 1 et 2
    mvwprintw(fenetre, 15, 2, "MENU\n");
    mvwprintw(fenetre, 16, 2, "1. 1 Joueur\n");
    mvwprintw(fenetre, 17, 2, "2. Autoplayer\n");
    mvwprintw(fenetre, 18, 2, "Entrer votre choix : ");
    mvwscanw(fenetre, 18, 22.52, "%d", &input);

    // Vérifier si l'entrée est valide (1 ou 2)
    if (input != 1 && input != 2) {
        mvwprintw(fenetre, 19, 2, "Choix invalide. Veuillez entrer 1 ou 2.");
    }

    wrefresh(fenetre);
}
