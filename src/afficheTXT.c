#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "afficheTXT.h"


/*////////////////////
// AFFICHAGE DU JEU //
////////////////////*/


// Première partie de afficherJeu
void afficherNiveau(const Niveau *n)
{
    int i, j;
    for (i = 0; i < n->dimx; i++)
    {
        for (j = 0; j < n->dimy; j++)
        {
            printf("%d ", obtenirElementNiveau(n, j, i));
        }
        printf("\n");
    }
}


// Deuxième et dernière partie de afficherJeu
void afficherNumNiveau(const Niveau *n)
{
    printf("%d\n", n->num);
}


void afficherJeu(const Jeu *j)
{
    afficherNiveau(&(j->niveau));
    printf("%s\n", (j->joueur).pseudo);
    printf("Niveau : ");
    afficherNumNiveau(&(j->niveau));
}


void boucleJeu(Jeu *j)
{
    char touche;
    while (!finJeu(j))
    {
        do
        {
            afficherJeu(j);
            getchar();
            printf("\nProchain mouvement : ");
            scanf("%c", &touche);
			if (touche != 'h' && touche != 'b' && touche != 'g' && touche != 'd' && touche != 'q'){
				printf("\nInstructions :\n");
				printf("\nh : haut\n");
				printf("b : bas\n");
				printf("g : gauche\n");
				printf("d : droite\n");
				printf("q : quitter\n\n");
			}
            else if (touche == 'q') return;
            else jeuClavier(j, touche);
        }
        while (!finNiveau(&j->niveau));

        if (j->niveau.num < nbNiveaux()) niveauSuivant(j);
        else (j->niveau.num++); // Indique la fin du jeu
    }
    printf("\nMerci d'avoir joué !\n");
}



/*/////////////////////
// AFFICHAGE DU MENU //
/////////////////////*/


void nouvellePartie()
{
    Jeu j;
    char pseudo[16];
    printf("Choisissez un pseudo : ");
    scanf("%s", pseudo);
	printf("%s", pseudo);
    fflush(stdout);
    printf("\n");
    initialiserJeu(&j, pseudo);
	creerJoueur(&(j.joueur), pseudo);
    boucleJeu(&j);
    quitterJeu(&j);
}


// Pour chargerPartie
void afficherJoueurs()
{
    DIR *dir = NULL;
	dir = opendir("data/joueurs");
    struct dirent *entry = NULL;
    while ((entry = readdir(dir)))
    {
        if (strcmp(entry->d_name, ".") == 0) continue;
        if (strcmp(entry->d_name, "..") == 0) continue;
        char *pDot = strchr(entry->d_name, '.');
        *pDot = '\0';
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}


void chargerPartie()
{
    Jeu j;
    char pseudo[16];
    afficherJoueurs();
    printf("Choisissez une partie : ");
    scanf("%s", pseudo);
	
	// Vérifie que la partie existe
	int pseudo_ok = 0;
	DIR *dir = NULL;
	dir = opendir("data/joueurs");
    struct dirent *entry = NULL;
    while ((entry = readdir(dir)))
    {
        if (strcmp(entry->d_name, ".") == 0) continue;
        if (strcmp(entry->d_name, "..") == 0) continue;
        char *pDot = strchr(entry->d_name, '.');
        *pDot = '\0';
        if (strcmp(pseudo, entry->d_name) == 0) pseudo_ok = 1;
    }

	if (pseudo_ok)
	{
		chargerJeu(&j, pseudo);
		boucleJeu(&j);
		quitterJeu(&j);
	}
	else
	{
		printf("Cette partie n'existe pas !\n");
		return; // Retour au menu
	}
}


void afficherMenu(const Menu *m)
{
    printf("\n\nMenu\n\n");
    int i;
    for (i = 0; i < m->nb_lignes; i++)
    {
        printf("%d : %s\n", i, (m->lignes[i]).texte);
    }
    printf("\nVotre choix ?\n");
    fflush(stdout);
}


int menuQuestion(const Menu *m)
{
    int cm;
    char dum[32];
    int ok = 0;
    do
    {
        if (scanf("%d",&cm)!=1) scanf("%s",dum);
        if ((cm < 0) || (cm >= m->nb_lignes))
            printf("Choix non valide !\n");
        else ok = 1;
        fflush(stdout);
    }
    while(ok == 0);
    printf("\n");
    fflush(stdout);
    return cm;
}


void boucleMenu(Menu *m)
{
	int cm;
	while(1)
    {
		afficherMenu(m);
		cm = menuQuestion(m);
		if (cm == 2){ // Quitter
			printf("Au revoir !\n");
			return;
		}
		else m->lignes[cm].commande();
	}
}
