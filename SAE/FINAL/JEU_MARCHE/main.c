#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

#define LIGNES 2
#define COLONNES 6
int main()
{
    executerJeu();
    afficherMenu();
    jeuDesPaires();
    initialiserCartes();
    melangerCartes();
    afficherCarte();
    afficherCartes();
    jeuDesCartes();

}
