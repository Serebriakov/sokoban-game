#include <stdlib.h>
#include <stdio.h>
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
    strcpy(fichier, "../data/niveaux/");
    strcat(fichier, niv);
    strcat(fichier, ".sok");

    FILE *fic = fopen(fichier, "r");
    fscanf(fic, "%d%d", &dimx, &dimy);

    /* On récupère le tableau d'entiers du niveau */
    char ligneFichier[dimx*dimy+1];
    fgets(ligneFichier, dimx*dimy+1, fic);
    fclose(fic);

    /* On adapte la taille du niveau */
    libererNiveau(n);
    initialiserNiveau(n, dimx, dimy);

    /* On recopie les données récupérées */
    n->num = niv;
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
                n->tab[j][i] = 0;
                break;
            case '1': // Cible
                n->tab[j][i] = 1;
                break;
            case '2': // Caisse
                n->tab[j][i] = 2;
                break;
            case '3': // Mur
                n->tab[j][i] = 3;
                break;
            case '4': // Elem4
                n->tab[j][i] = 4;
                break;
            case '5': // Elem5
                n->tab[j][i] = 5;
                break;
            case '6': // Elem6
                n->tab[j][i] = 6;
                break;
            case '7': // Elem7
                n->tab[j][i] = 7;
                break;
            case '8': // Elem8
                n->tab[j][i] = 8;
                break;
            case '9': // Elem9
                n->tab[j][i] = 9;
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
	return n->tab[y][x];
}


void modifierElementNiveau(const Niveau *n, int x, int y, int e)
{
    assert(x >= 0);
	assert(y >= 0);
	assert(x < n->dimx);
	assert(y < n->dimy);
    n->tab[y][x] = e;
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
            fprintf(fic, "%d", n->tab[j][i]);
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
