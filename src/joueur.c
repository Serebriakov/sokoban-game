#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "joueur.h"
#include "constantes.h"


int obtenirAvancement(const Joueur *j)
{
    return j->avancement;
}


void modifierAvancement(Joueur* j, int niv)
{
    j->avancement = niv;
}
