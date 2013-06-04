#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "niveau.h"


void initialiserNiveau(Niveau *n, int dimx, int dimy)
{
    int i, j;
	n->dimx = dimx;
	n->dimy = dimy;
	n->tab = (int **)malloc(sizeof(int*)*dimy);
	for (i=0; i < n->dimy; i++)
		n->tab[i] = (int *)malloc(sizeof(int)*n->dimx);
	for (i = 0; i<dimy; i++)
	{
		for (j=0; j<dimx; j++)
		{
			n->tab[i][j] = VIDE;
		}
	}
}


int obtenirDimXNiveau(const Niveau *n)
{
	return n->dimx;
}

int obtenirDimYNiveau(const Niveau *n)
{
	return n->dimy;
}


int obtenirNumNiveau(const Niveau *n)
{
	return n->num;
}


void modifierNumNiveau(Niveau *n, int niv)
{
	n->num = niv;
}


int obtenirElementNiveau(const Niveau *n, int x, int y)
{
	assert(x < n->dimx);
	assert(y < n->dimy);
	return n->tab[y][x];
}


void modifierElementNiveau(Niveau *n, int x, int y, int e)
{
	assert(x < n->dimx);
	assert(y < n->dimy);
    n->tab[y][x] = e;
}


void libererNiveau(Niveau *n)
{   
	int i;
	for (i=0; i<n->dimy; i++)
	{
		free (n->tab[i]);
		n->tab[i] = NULL;
	}
	free(n->tab);
	n->tab = NULL;
}

void testRegressionNiveau()
{
	// Test procédure initialiserNiveau, obtenirDimXNiveau et obtenirDimYNiveau
	Niveau n;
	initialiserNiveau(&n, 8, 6);
	assert (obtenirDimXNiveau(&n) == 8 && obtenirDimYNiveau(&n) == 6);
	int i, j;
	for (i=0; i<obtenirDimYNiveau(&n); i++)
		for (j=0; j<obtenirDimXNiveau(&n); j++)
			assert(obtenirElementNiveau(&n, j, i) == VIDE);

	// Test procédure modifierNumNiveau et obtenirNumNiveau
	modifierNumNiveau(&n, 4);
	assert(obtenirNumNiveau(&n) == 4);

	// Test procédure modifierElementNiveau et obtenirElementNiveau
	modifierElementNiveau(&n, 4, 5, JOUEUR);
	assert(obtenirElementNiveau(&n, 4, 5) == JOUEUR);

	// Test procédure libererNiveau
	libererNiveau(&n);
	assert((n.tab) == NULL);
}
