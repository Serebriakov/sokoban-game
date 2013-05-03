#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "niveau.h"


void initialiserNiveau(Niveau *n, int dimx, int dimy)
{
	int i;

    n->tab = (int **) malloc(sizeof(int*)*dimy);
	int *tab2 = (int *) malloc(sizeof(int)*dimx*dimy);
	for(i = 0 ; i < dimy ; i++)
	{
		n->tab[i] = &tab2[i*dimx];
	}
	n->dimx = dimx;
	n->dimy = dimy;
}


int obtenirElementNiveau(const Niveau *n, int x, int y)
{
	assert(x < n->dimx);
	assert(y < n->dimy);
	return n->tab[x][y];
}


void modifierElementNiveau(Niveau *n, int x, int y, int e)
{
	assert(x < n->dimx);
	assert(y < n->dimy);
    n->tab[x][y] = e;
}


void libererNiveau(Niveau *n)
{
    n->dimx = 0;
    n->dimy = 0;
    free(n->tab[0]);
    free(n->tab);
}
