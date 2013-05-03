#include <stdlib.h>
#include <stdio.h>

#include "afficheTXT.h"
#include "joueur.h"
#include "jeu.h"
#include "menu.h"
#include "fichiers.h"


void nouvellePartie()
{
    Jeu j;
    char pseudo[36];
    printf("Entrez le nom du joueur : ");
    scanf("%s", pseudo);
    fflush(stdout);
    printf("\n");
    initialiserJeu(&j, pseudo);
    boucleJeu(&j);
    quitterJeu(&j);
}


void chargerPartie()
{
    Jeu j;
    char pseudo[16];
    afficherJoueurs();
    printf("Entrez le nom du joueur : ");
    scanf("%s", pseudo);
    chargerJeu(&j, pseudo);
    boucleJeu(&j);
    quitterJeu(&j);
}


void quitter()
{
    printf("Au revoir !\n");
    exit(EXIT_SUCCESS);
}


int main()
{
    Menu m;
    menuInit(&m);
    menuAjouterLigne(&m, "Nouvelle partie", nouvellePartie);
    menuAjouterLigne(&m, "Charger une partie", chargerPartie);
    menuAjouterLigne(&m, "Quitter", quitter);
    boucleMenu(&m);
    menuLibere(&m);
    return 0;
}
