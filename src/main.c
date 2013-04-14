#include <stdlib.h>
#include <stdio.h>

#include "AfficheTXT.h"
#include "Joueur.h"
#include "Jeu.h"
#include "Menu.h"


void nouvellePartie()
{
    Jeu j;
    char pseudo[36];
    scanf("Entrez le nom du joueur : %s", pseudo);
    initialiserJeu(&j, pseudo);
    boucleJeu(&j);
    quitterJeu(&j);
}


void chargerPartie()
{
    Joueur p;
    afficherJoueurs();
    char pseudo[16];
    scanf("Entrez le nom d'un joueur : %s", pseudo);
    chargerJoueur(&p, pseudo);
    Jeu j;
    char avancement[3];
    sprintf(avancement, "%d", p.avancement);
    chargerJeu(&j, p.pseudo, avancement);
    boucleJeu(&j);
    quitterJeu(&j);
}


void quitter()
{
    printf("Au revoir !\n");
    exit(0);
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
