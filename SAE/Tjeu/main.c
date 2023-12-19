#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

// Prototypes des fonctions
void afficherMenu();
void jeuDesPaires();

int input;

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
        // Appeler la fonction jeuDesPaires si l'option 1 est choisie
        if (input == 1) {
            curs_set(FALSE);
            clear();
            jeuDesPaires();
        }
    } while (input != 2);

    endwin();

    return 0;
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
    mvwprintw(fenetre, 16, 2, "1. Jeu des paires\n");
    mvwprintw(fenetre, 17, 2, "2. Autoplayer\n");
    mvwprintw(fenetre, 18, 2, "Entrer votre choix : ");
    mvwscanw(fenetre, 18, 22.52, "%d", &input);

    wrefresh(fenetre);
}

void jeuDesPaires() {
    // Votre code du jeu des paires ici...

    // Exemple de code :
    WINDOW *box1 = subwin(stdscr, 5, 50, 1, 1);
    box(box1, ACS_VLINE, ACS_HLINE);
    mvwprintw(box1, 0, (50 - 15) / 2, "Jeu des paires");
    wrefresh(box1);

    // Attendre une touche pour quitter le jeu
    getch();
    delwin(box1);
}

void drawBox(WINDOW *box, int height, int width, int starty, int startx, const char *title, const char *content) {
    wborder(box, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(box, 0, (width - strlen(title)) / 2, title);
    wrefresh(box);

    mvwprintw(box, 2, 2, content);
    wrefresh(box);
}

void drawChrono(WINDOW *box, int height, int width, int starty, int startx) {
    wborder(box, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(box, 0, (width - 7) / 2, "Chrono");
    wrefresh(box);

    time_t start_time = time(NULL);
    while (1) {
        time_t current_time = time(NULL);
        int elapsed_time = difftime(current_time, start_time);

        mvwprintw(box, 2, 2, "Temps écoulé: %02d:%02d", elapsed_time / 60, elapsed_time % 60);
        wrefresh(box);

        //napms(1000); // Attente d'une seconde
    }
}
