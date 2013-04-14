#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "Niveau.h"


void initialiserNiveau(Niveau *n, int dimx, int dimy)
{
    n->tab = (int **) malloc(sizeof(int*)*dimy);
	int *tab2 = (int *) malloc(sizeof(int)*dimx*dimy);
	int i;
	for(i = 0 ; i < dimy ; i++)
	{
		n->tab[i] = &tab2[i*dimx];
	}
}


void chargerNiveau(Niveau *n, const char *niv)
{
    int dimx;
    int dimy;

    /* On récupère les dimensions du niveau */
    char fichier[36];
    strcpy(fichier, "data/niveaux/");
    strcat(fichier, niv);
    strcat(fichier, ".sok");

    FILE *fic = fopen(fichier, "r");
    fscanf(fic, "%d %d ", &dimx, &dimy);

    /* On récupère le tableau d'entiers du niveau */
    char ligneFichier[dimx*dimy+1];
    fgets(ligneFichier, dimx*dimy+1, fic);
    fclose(fic);

    /* On adapte la taille du niveau */
    libererNiveau(n);
    initialiserNiveau(n, dimx, dimy);

    /* On recopie les données récupérées */
    n->num = atoi(niv);
    n->dimx = dimx;
    n->dimy = dimy;
    int i, j;
    for (i = 0; i < dimx; i++)
    {
        for (j = 0; j < dimy; j++)
        {
            switch(ligneFichier[i*dimx+j])
            {
            case '0': // Joueur
                n->tab[i][j] = 0;
                break;
            case '1': // Vide
                n->tab[i][j] = 1;
                break;
            case '2': // Case cible
                n->tab[i][j] = 2;
                break;
            case '3': // Caisse
                n->tab[i][j] = 3;
                break;
            case '4': // Caisse sur une case cible
                n->tab[i][j] = 4;
                break;
            case '5': // Mur
                n->tab[i][j] = 5;
                break;
            case '6': // Element decor
                n->tab[i][j] = 6;
                break;
            case '7': // Element décor
                n->tab[i][j] = 7;
                break;
            case '8': // Element décor
                n->tab[i][j] = 8;
                break;
            case '9': // Element décor
                n->tab[i][j] = 9;
                break;
            }
        }
    }
}


int obtenirElementNiveau(const Niveau *n, int x, int y)
{
    assert(x >= 0);
	assert(y >= 0);
	assert(x < n->dimx);
	assert(y < n->dimy);
	return n->tab[x][y];
}


void modifierElementNiveau(const Niveau *n, int x, int y, int e)
{
    assert(x >= 0);
	assert(y >= 0);
	assert(x < n->dimx);
	assert(y < n->dimy);
    n->tab[x][y] = e;
}


void sauvegarderNiveau(const Niveau *n, const char *fichier)
{
    FILE *fic = fopen(fichier, "w");
    fprintf(fic, "%d", n->dimx);
    fprintf(fic, "%d", n->dimy);
    int i, j;
    for (i = 0 ; i < n->dimx ; i++)
    {
        for (j = 0 ; j < n->dimy ; j++)
        {
            fprintf(fic, "%d", n->tab[i][j]);
        }
    }
    fclose(fic);
}


void libererNiveau(Niveau *n)
{
    n->dimx = 0;
    n->dimy = 0;
    free(n->tab[0]);
    free(n->tab);
}
