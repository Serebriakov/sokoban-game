#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Menu.h"


void menuInit(Menu* m)
{
    m->nb_lignes = 0;
}


void menuAjouterLigne(Menu* m, char* texte, MenuFonction fonction)
{
    assert(m->nb_lignes<32);
    strcpy(m->lignes[m->nb_lignes].texte, texte);
    m->lignes[m->nb_lignes].commande = fonction;
    m->nb_lignes++;
}


void menuLibere(Menu* m)
{
    m->nb_lignes = 0;
}

