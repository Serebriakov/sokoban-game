#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "afficheTXT.h"
#include "constantes.h"
#include "niveau.h"


void afficherJoueurs()
{
    DIR *dir = opendir("data/joueurs");
    struct dirent *entry;
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



void afficherAvancementJoueur(Joueur *j)
{
    printf("%d\n", obtenirAvancement(j));
}


void afficherNumNiveau(const Niveau *n)
{
    printf("%d\n", n->num);
}


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


void afficherMenu(const Menu *m)
{
    printf("\n\nMenu\n\n");
    int i;
    for (i = 0; i < m->nb_lignes; i++)
    {
        printf("%d : %s\n", i, (m->lignes[i]).texte);
    }
    printf("Votre choix ?\n");
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
            printf("Erreur choix menu\n");
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
		m->lignes[cm].commande();
	}
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
            if (touche == 'q') return;
            else jeuClavier(j, touche);
        }
        while (!finNiveau(&j->niveau));

        if (j->niveau.num < NB_NIVEAUX) niveauSuivant(j);
        else (j->niveau.num++); // Indique la fin du jeu
    }
    printf("\nMerci d'avoir joué !\n");
}
