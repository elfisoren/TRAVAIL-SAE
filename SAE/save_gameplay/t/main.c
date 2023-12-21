#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define LIGNES 2
#define COLONNES 6

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








void afficherCartes(char cartes[LIGNES * COLONNES], bool cartesVisibles[LIGNES * COLONNES], int carteSelectionnee) {
    for (int i = 0; i < LIGNES * COLONNES; ++i) {
        bool estSelectionnee = (i == carteSelectionnee);
        afficherCarte(i, cartes[i], cartesVisibles[i], estSelectionnee);
    }
}









void afficherCarte(int indice, char carte, bool carteVisible, bool estSelectionnee) {
   if (estSelectionnee) {
                                                                                //attron(A_REVERSE); // Activer l'inversion des couleurs
        attron(COLOR_PAIR(1));                                                  // Rouge pour la sélection
    } else if (carteVisible) {
                                                                                //attron(COLOR_PAIR(2)); // Vert pour les cartes retournées
    }
    int hauteur = LINES / 2 - 4 + (indice / COLONNES) * 4;
    int largeur = COLS / 2 - 24 + (indice % COLONNES) * 8;

    mvprintw(hauteur, largeur, " #-----#");
    mvprintw(hauteur + 1, largeur, " #     #");
    mvprintw(hauteur + 2, largeur, " #  %c  #", carteVisible ? carte : ' ');
    mvprintw(hauteur + 3, largeur, " #-----#");

    if (estSelectionnee || carteVisible) {
        attroff(COLOR_PAIR(1));
    }
}





void afficherTimer(time_t debutTimer) {
   if (debutTimer != 0) {
        time_t maintenant = time(NULL);
        int duree = (int)difftime(maintenant, debutTimer);
        mvprintw(LIGNES * 4, 0, "Temps écoulé : %d secondes", duree);
    }
}

void jouerMemory() {
    char cartes[LIGNES * COLONNES];
    bool cartesVisibles[LIGNES * COLONNES] = {false};

    initialiserCartes(cartes);
    melangerCartes(cartes);

    int carteSelectionnee = 0;
    int cartePrecedente = -1;

    int pairesTrouvees = 0;
    time_t debutTimer = 0;
    bool timerDemarre = false;

    clear();  // Déplacer l'effacement de l'écran à l'extérieur de la boucle principale

    while (pairesTrouvees < LIGNES * COLONNES / 2) {
        afficherCartes(cartes, cartesVisibles, carteSelectionnee);
        afficherTimer(debutTimer);
        refresh();

        int choix = getch();

        switch (choix) {
            case 'a':
                do {
                    carteSelectionnee = (carteSelectionnee - 1 + LIGNES * COLONNES) % (LIGNES * COLONNES);
                } while (cartesVisibles[carteSelectionnee]);
                break;
            case 'z':
                do {
                    carteSelectionnee = (carteSelectionnee + 1) % (LIGNES * COLONNES);
                } while (cartesVisibles[carteSelectionnee]);
                break;
            case 'e':
                if (!timerDemarre) {
                    debutTimer = time(NULL);
                    timerDemarre = true;
                }
                if (!cartesVisibles[carteSelectionnee]) {
                    cartesVisibles[carteSelectionnee] = true;
                    afficherCartes(cartes, cartesVisibles, carteSelectionnee);
                    refresh();

                    if (cartePrecedente != -1) {
                        napms(2000);
                        if (cartes[carteSelectionnee] == cartes[cartePrecedente]) {
                            printw("\nBravo ! Vous avez trouvé une paire.\n");
                            pairesTrouvees++;
                        } else {
                            printw("\nDommage. Les cartes ne correspondent pas.\n");
                            cartesVisibles[carteSelectionnee] = false;
                            cartesVisibles[cartePrecedente] = false;
                            refresh();
                        }
                        cartePrecedente = -1;
                    } else {
                        cartePrecedente = carteSelectionnee;
                    }
                }
                break;
        }

        napms(100);
    }

    printw("\nFélicitations ! Vous avez trouvé toutes les paires.\n");
    afficherTimer(debutTimer);
}


int main() {
    initscr();
    curs_set(0);
    noecho();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    raw();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    jouerMemory();  // Appeler la fonction pour jouer au Memory

    endwin();

    return 0;
}
