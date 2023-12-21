#include <stdio.h>
#include <stdlib.h>
#include "Tools.h"

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
}

