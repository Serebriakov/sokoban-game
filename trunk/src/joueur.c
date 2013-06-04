#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "joueur.h"


int obtenirAvancement(const Joueur *j)
{
    return j->avancement;
}


void modifierAvancement(Joueur *j, int niv)
{
    j->avancement = niv;
}


int obtenirScore(const Joueur *j, int niv)
{
	return j->scores[niv];
}


void modifierScore(Joueur *j, int niv, int score)
{
	j->scores[niv] = score;
}


void testRegressionJoueur()
{
	// Test procédures modifierAvancement et obtenirAvancement
	Joueur j;
	modifierAvancement(&j, 4);
	assert(obtenirAvancement(&j) == 4);

	// Tests procédures modifierScore et obtenirScore
	modifierScore(&j, 4, 942);
	assert(obtenirScore(&j, 4) == 942);
}

