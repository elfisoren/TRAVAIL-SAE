#include <ncurses.h>
#include <string.h>
#include <time.h>


#define BOX1_HEIGHT 5
#define BOX1_WIDTH 50
#define BOX1_Y 1
#define BOX1_X 1

#define BOX2_HEIGHT 5
#define BOX2_WIDTH 27
#define BOX2_Y 1
#define BOX2_X 52

#define BOX3_HEIGHT 5
#define BOX3_WIDTH 2
#define BOX3_Y 18
#define BOX3_X 1

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

int main() {
    initscr(); // Initialisation de ncurses
    curs_set(0); // Cacher le curseur
    keypad(stdscr, TRUE); // Activer les touches spéciales

    int max_y, max_x;

    getmaxyx(stdscr, max_y, max_x);

    // Vérifier si la fenêtre est assez grande pour afficher les boîtes
    if (max_y < BOX2_Y + BOX2_HEIGHT || max_x < BOX2_X + BOX2_WIDTH) {
        endwin();
        printf("La fenêtre est trop petite.\n");
        return 1;
    }

    // Création de la première boîte avec subwin
    WINDOW *box1 = subwin(stdscr, BOX1_HEIGHT, BOX1_WIDTH, BOX1_Y, BOX1_X);
    drawBox(box1, BOX1_HEIGHT, BOX1_WIDTH, BOX1_Y, BOX1_X, "Jeu des paires", "Trouver les paires en un minimum de temps");

    // Création de la deuxième boîte avec subwin
    WINDOW *box2 = subwin(stdscr, BOX2_HEIGHT, BOX2_WIDTH, BOX2_Y, BOX2_X);
    drawChrono(box2, BOX2_HEIGHT, BOX2_WIDTH, BOX2_Y, BOX2_X);

    WINDOW *box3 = subwin(stdscr,BOX3_HEIGHT, BOX3_WIDTH, BOX3_Y, BOX3_X);
    drawBox(box3,BOX3_HEIGHT, BOX3_WIDTH, BOX3_Y, BOX3_X,"test","tttt");

    // Attendre une touche pour quitter
    getch();

    endwin(); // Fermeture de ncurses
    return 0;
}
