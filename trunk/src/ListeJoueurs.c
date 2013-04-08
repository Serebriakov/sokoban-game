#include <stdlib.h>
#include <stdio.h>

#include "ListeJoueurs.h"


void initialiserListe(ListeJoueurs * l)
{
    l->prem = NULL;
    l->last = NULL;
}


int estVideListe(const ListeJoueurs * l)
{
    if (l->prem == NULL) return 1;
    else return 0;
}


unsigned int nbElementsListe(const ListeJoueurs * l)
{
    int nbElementsListe = 0;
    CelluleJoueur *tmp = l->prem;
    while (tmp != NULL)
    {
        nbElementsListe++;
        tmp = tmp->suivant;
    }
    return nbElementsListe;
}


Joueur iemeElementListe(const ListeJoueurs * l, unsigned int i)
{
    int j;
    CelluleJoueur *tmp = l->prem;
    for (j=0; j<i; j++)
    {
        tmp = tmp->suivant;
    }
    return tmp->info;
}


void modifierIemeElementListe(const ListeJoueurs * l, unsigned int i, const Joueur j)
{
    int k;
    CelluleJoueur *tmp = l->prem;
    for (k=0; k<i; k++)
    {
        tmp = tmp->suivant;
    }
    tmp->info = j;
}


void ajouterEnTeteListe(const Joueur j, ListeJoueurs * l)
{
    if (l->prem == NULL)
    {
        l->prem = malloc(sizeof(CelluleJoueur));
        l->last = l->prem;
        l->prem->precedent = NULL;
        l->prem->suivant = NULL;
        l->prem->info = j;
    }
    else
    {
        CelluleJoueur *tmp = l->prem;
        l->prem = malloc(sizeof(CelluleJoueur));
        tmp->precedent = l->prem;
        l->prem->precedent = NULL;
        l->prem->suivant = tmp;
        l->prem->info = j;
    }
}


void ajouterEnQueueListe(const Joueur j, ListeJoueurs * l)
{
    if (l->last == NULL)
    {
        l->last = malloc(sizeof(CelluleJoueur));
        l->prem = l->last;
        l->last->precedent = NULL;
        l->last->suivant = NULL;
        l->last->info = j;
    }
    else
    {
        CelluleJoueur *tmp = l->last;
        l->last = malloc(sizeof(CelluleJoueur));
        tmp->suivant = l->last;
        l->last->precedent = tmp;
        l->last->suivant = NULL;
        l->last->info = j;
    }
}


void supprimerTeteListe(ListeJoueurs * l)
{
    if (l->prem == l->last)
    {
        free(l->prem);
        l->prem = NULL;
        l->last = NULL;
    }
    else
    {
        CelluleJoueur *tmp = l->prem->suivant;
        free(l->prem);
        l->prem = tmp;
        tmp->precedent = NULL;
    }
}


void viderListe(ListeJoueurs * l)
{
    while (!estVideListe(l))
    {
        supprimerTeteListe(l);
    }
}


void testamentListe(ListeJoueurs * l)
{
    viderListe(l);
}


void affecterListe(ListeJoueurs * l1, const ListeJoueurs * l2)
{
    viderListe(l1);
    CelluleJoueur *tmp = l2->prem;
    while (tmp != NULL)
    {
        ajouterEnQueueListe(tmp->info, l1);
        tmp = tmp->suivant;
    }
}


int rechercherElementListe(const Joueur j, const ListeJoueurs *l)
{
    int i;
    for (i=0; i<nbElementsListe(l); i++)
    {
        if (egaliteJoueur(iemeElementListe(l, i), j))
        {
            return i;
        }
    }
    return -1;
}


void insererElementListe(const Joueur j, ListeJoueurs * l, unsigned int position)
{
    if (position == 0)
    {
        ajouterEnTeteListe(j, l);
    }
    else if (position == nbElementsListe(l))
    {
        ajouterEnQueueListe(j, l);
    }
    else
    {
        int i;
        CelluleJoueur *tmp1 = l->prem; // Pointera sur l'élément suivant l'élément à insérer
        CelluleJoueur *tmp2; // Pointera sur l'élémént précédent l'élément à insérer
        for (i=0; i<position; i++)
        {
            tmp1 = tmp1->suivant;
            tmp2 = tmp1->precedent;
        }
        tmp2->suivant = malloc(sizeof(CelluleJoueur));
        tmp1->precedent = tmp2->suivant;
        tmp2->suivant->precedent = tmp2;
        tmp2->suivant->suivant = tmp1;
        tmp2->suivant->info = j;
    }
}
