
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

char autoplayer()
{
char l[3] = {'a','z',10};
    int i = rand() % 3;
    return l[i];

}


void afficherCartes(char cartes[LIGNES * COLONNES], bool cartesVisibles[LIGNES * COLONNES], int carteSelectionnee) {
    for (int i = 0; i < LIGNES * COLONNES; ++i) {
        bool estSelectionnee = (i == carteSelectionnee);
        afficherCarte(i, cartes[i], cartesVisibles[i], estSelectionnee);
    }
}

void afficherTimer(time_t debutTimer) {
    if (debutTimer != 0) {
        time_t maintenant = time(NULL);
        int duree = (int)difftime(maintenant, debutTimer);
        mvprintw(LIGNES * 4, 0, "Temps écoulé : %d secondes", duree);
    }
}

int main() {
    initscr(); // Initialiser l'environnement ncurses
    curs_set(0);
    noecho();
    start_color(); // Activer la prise en charge des couleurs
    init_pair(1, COLOR_RED, COLOR_BLACK); // Rouge pour la sélection et les cartes retournées
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // Vert pour les cartes retournées

    raw(); // Désactiver le buffering de ligne
    keypad(stdscr, TRUE); // Activer la prise en charge des touches spéciales
    nodelay(stdscr, TRUE); // Mode non bloquant pour getch()

    char cartes[LIGNES * COLONNES];
    bool cartesVisibles[LIGNES * COLONNES] = {false};

    initialiserCartes(cartes);
    melangerCartes(cartes);

    int carteSelectionnee = 0;
    int cartePrecedente = -1;

    int pairesTrouvees = 0;
    time_t debutTimer = 0;
    bool timerDemarre = false; // Nouvelle variable pour gérer le démarrage du timer

    while (pairesTrouvees < LIGNES * COLONNES / 2) {
        clear(); // Effacer l'écran

        afficherCartes(cartes, cartesVisibles, carteSelectionnee);
        afficherTimer(debutTimer); // Afficher le timer
        refresh(); // Rafraîchir l'écran

        int choix = getch();//autoplayer(); // Obtenir la touche pressée

        switch (choix) {
            case 'a':
                do {
                    carteSelectionnee = (carteSelectionnee - 1 + LIGNES * COLONNES) % (LIGNES * COLONNES);
                } while (cartesVisibles[carteSelectionnee]); // Passer à la carte précédente non retournée
                break;
            case 'z':
                do {
                    carteSelectionnee = (carteSelectionnee + 1) % (LIGNES * COLONNES);
                } while (cartesVisibles[carteSelectionnee]); // Passer à la carte suivante non retournée
                break;
            case 'e': // Touche "Entrée" pour retourner la carte
                if (!timerDemarre) {
                        debutTimer = time(NULL); // Démarrer le timer lorsque la première carte est retournée
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

        napms(100); // Ajouter un léger délai pour améliorer la lisibilité
    }

    printw("\nFélicitations ! Vous avez trouvé toutes les paires.\n");
    afficherTimer(debutTimer); // Afficher le temps total

    endwin(); // Terminer l'environnement ncurses

    return 0;
}
