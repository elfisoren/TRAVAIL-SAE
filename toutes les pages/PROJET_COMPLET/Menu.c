#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "Tools.h"

int a;

int main(void)
{
    WINDOW *fenetre;

    int choix;
    initscr();

    curs_set(TRUE);

    fenetre = subwin(stdscr,0,0,0,0);
    box(fenetre,ACS_VLINE,ACS_HLINE);

    mvwprintw(fenetre, 1, 4,"-------------------------------------------------------------------------");
    mvwprintw(fenetre, 2, 4,"    * **** *   *   ***   ****   **    ***     *      *   ****   ****   **");
    mvwprintw(fenetre, 3, 4,"    * *    *   *   *  *  *     *      *  *   * *     *   *  *   *     *  ");
    mvwprintw(fenetre, 4, 4,"    * **   *   *   *  *  **     *     * *   *****    *   * *    **     * ");
    mvwprintw(fenetre, 5, 4," *  * *    *   *   *  *  *       *    *    *     *   *   *  *   *        *");
    mvwprintw(fenetre, 6, 4,"  **  ****  ***    ***   ****  **     *   *       *  *   *   *  ****  ** ");
    mvwprintw(fenetre, 7, 4,"-------------------------------------------------------------------------");

    // affichage menu avec l'option 1 et 2
    mvwprintw(fenetre, 11,4,"MENU");
    mvwprintw(fenetre, 13,4,"1. 1 Joueur");
    mvwprintw(fenetre, 15,4,"2. Autoplayer");

    //CHOIX
    mvwprintw(fenetre, 18,4,"Entrer votre choix : \n");
    mvwscanw(fenetre,19,4,"%d",&a);
    switch(a)
    {
    case 1:
        mvwprintw(fenetre, 21,4,"Vous avez choisit 1 joueur redirection en cours");//passer à la page 2 1 joueur                    //fonction page 1Joueur
        break;
    case 2:
        mvwprintw(fenetre, 21,4,"Vous avez choisit Autoplayer redirection en cours");                                               //fonction page autoplayer
        //passer a la page 2 Autoplayer
        break;
    default:
        mvwprintw(fenetre, 21,4,"Choisissez une valeur, soit 1 soit 2.");
        break;
    }
                                                                                                                                    //après le switch continuer avec les fonctions afin de lancer le jeu souhaiter
    wrefresh(fenetre);
    getch();
    //scanf("%d",&choix);
    //printw("%d",choix);

    endwin();
    free(fenetre);

    return 0;




}
