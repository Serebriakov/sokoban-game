#include <stdio.h>
#include <string.h>

#include "jeu.h"
#include "fichiers.h"
#include "constantes.h"


void initialiserJeu(Jeu *j, const char *pseudo)
{
    creerJoueur(&(j->joueur), pseudo);
    initialiserNiveau(&(j->niveau), 1, 1);
    chargerNiveau(&(j->niveau), 1);
}


void chargerJeu(Jeu *j, const char *pseudo)
{
    chargerJoueur(&(j->joueur), pseudo);
    initialiserNiveau(&(j->niveau), 1, 1);
    chargerNiveau(&(j->niveau), (j->joueur).avancement);
}


// Procédure auxiliaire //
void changerNiveau(Jeu *j, int niv)
{
    chargerNiveau(&(j->niveau), niv);
}


void niveauSuivant(Jeu *j)
{
    changerNiveau(j, j->joueur.avancement + 1);
}


// Fonction auxiliaire //
Position obtenirPositionJoueur(const Niveau *n)
{
    int x, y;
    Position pos;
    for (x = 0; x < n->dimx; x++)
    {
        for (y = 0; y < n->dimy; y++)
        {
            if (obtenirElementNiveau(n, x, y) == JOUEUR || obtenirElementNiveau(n, x, y) == JOUEUR_CIBLE)
            {
                pos.x = x;
                pos.y = y;
                return pos;
            }
        }
    }
    pos.x = -1;
    pos.y = -1;
    return pos;
}


// Procédure auxiliaire //
void joueurGauche(Niveau *n)
{
    Position pos_joueur;
    obtenirPositionJoueur(n);
    int elem_gauche; // On va regarder l'élément à gauche du joueur
    int elem_gauche_gauche; // Mais également l'élément encore à gauche

    pos_joueur = obtenirPositionJoueur(n);

    if (pos_joueur.x-1 >= 0)
    {
        elem_gauche = obtenirElementNiveau(n, pos_joueur.x-1, pos_joueur.y);
    }
    else
    {
        elem_gauche = MUR;
    }


    if (pos_joueur.x-2 >= 0)
    {
        elem_gauche_gauche = obtenirElementNiveau(n, pos_joueur.x-2, pos_joueur.y);
    }
    else
    {
        elem_gauche_gauche = MUR;
    }

    if (obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y) == JOUEUR) // Le joueur n'est pas sur une cible
    {
        if (elem_gauche == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR);
        }
        if (elem_gauche == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR_CIBLE);
        }
        if (elem_gauche == CAISSE && elem_gauche_gauche == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x-2, pos_joueur.y, CAISSE_OK);
        }
        if (elem_gauche == CAISSE && elem_gauche_gauche == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x-2, pos_joueur.y, CAISSE);
        }
    }

    if (obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y) == JOUEUR_CIBLE) // Le joueur est sur une cible
    {
        if (elem_gauche == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR);
        }
        if (elem_gauche == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR_CIBLE);
        }
        if (elem_gauche == CAISSE && elem_gauche_gauche == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x-2, pos_joueur.y, CAISSE_OK);
        }
        if (elem_gauche == CAISSE && elem_gauche_gauche == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x-2, pos_joueur.y, CAISSE);
        }
    }
}


// Procédure auxiliaire
void joueurDroite(Niveau *n)
{
    Position pos_joueur;
    int elem_droite; // On va regarder l'élément à droite du joueur
    int elem_droite_droite; // Mais également l'élément encore à droite

    pos_joueur = obtenirPositionJoueur(n);

    if (pos_joueur.x+1 < n->dimx)
    {
        elem_droite = obtenirElementNiveau(n, pos_joueur.x+1, pos_joueur.y);
    }
    else
    {
        elem_droite = MUR;
    }
    if (pos_joueur.x+2 < n->dimx)
    {
        elem_droite_droite = obtenirElementNiveau(n, pos_joueur.x+2, pos_joueur.y);
    }
    else
    {
        elem_droite_droite = MUR;
    }

    if (obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y) == JOUEUR) // Le joueur n'est pas sur une cible
    {
        if (elem_droite == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR);
        }
        if (elem_droite == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR_CIBLE);
        }
        if (elem_droite == CAISSE && elem_droite_droite == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x+2, pos_joueur.y, CAISSE_OK);
        }
        if (elem_droite == CAISSE && elem_droite_droite == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x+2, pos_joueur.y, CAISSE);
        }
    }

    if (obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y) == JOUEUR_CIBLE) // Le joueur est sur une cible
    {
        if (elem_droite == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR);
        }
        if (elem_droite == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR_CIBLE);
        }
        if (elem_droite == CAISSE && elem_droite_droite == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x+2, pos_joueur.y, CAISSE_OK);
        }
        if (elem_droite == CAISSE && elem_droite_droite == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x+2, pos_joueur.y, CAISSE);
        }
    }
}


// Procédure auxiliaire //
void joueurHaut(Niveau *n)
{
    Position pos_joueur;
    pos_joueur = obtenirPositionJoueur(n);
    int elem_haut; // On va regarder l'élément en haut du joueur
    int elem_haut_haut; // Mais également l'élément encore en haut

    if (pos_joueur.y-1 >= 0)
    {
        elem_haut = obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y-1);
    }
    else
    {
        elem_haut = MUR;
    }
    if (pos_joueur.y-2 >= 0)
    {
        elem_haut_haut = obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y-2);
    }
    else
    {
        elem_haut = MUR;
    }

    if (obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y) == JOUEUR) // Le joueur n'est pas sur une cible
    {
        if (elem_haut == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR);
        }
        if (elem_haut == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR_CIBLE);
        }
        if (elem_haut == CAISSE && elem_haut_haut == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-2, CAISSE_OK);
        }
        if (elem_haut == CAISSE && elem_haut_haut == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-2, CAISSE);
        }
    }
    if (obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y) == JOUEUR_CIBLE) // Le joueur est sur une cible
    {
        if (elem_haut == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR);
        }
        if (elem_haut == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR_CIBLE);
        }
        if (elem_haut == CAISSE && elem_haut_haut == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-2, CAISSE_OK);
        }
        if (elem_haut == CAISSE && elem_haut_haut == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-2, CAISSE);
        }
    }
}


// Procédure auxiliaire //
void joueurBas(Niveau *n)
{
    Position pos_joueur;
    int elem_bas; // On va regarder l'élément en bas du joueur
    int elem_bas_bas; // Mais également l'élément encore en bas

    pos_joueur = obtenirPositionJoueur(n);

    if (pos_joueur.y+1 < n->dimy)
    {
        elem_bas = obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y+1);
    }
    else
    {
        elem_bas = MUR;
    }
    if (pos_joueur.y+2 < n->dimy)
    {
        elem_bas_bas = obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y+2);
    }
    else
    {
        elem_bas_bas = MUR;
    }

    if (obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y) == JOUEUR) // Le joueur n'est pas sur une cible
    {
        if (elem_bas == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR);
        }
        if (elem_bas == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR_CIBLE);
        }
        if (elem_bas == CAISSE && elem_bas_bas == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+2, CAISSE_OK);
        }
        if (elem_bas == CAISSE && elem_bas_bas == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+2, CAISSE);
        }
    }

    if (obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y) == JOUEUR_CIBLE) // Le joueur est sur une cible
    {
        if (elem_bas == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR);
        }
        if (elem_bas == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR_CIBLE);
        }
        if (elem_bas == CAISSE && elem_bas_bas == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+2, CAISSE_OK);
        }
        if (elem_bas == CAISSE && elem_bas_bas == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+2, CAISSE);
        }
    }
}


void libererJeu(Jeu *j)
{
    libererNiveau(&(j->niveau));
}


void quitterJeu(Jeu *j)
{
    modifierAvancement(&(j->joueur), (j->niveau).num);
    sauvegarderJoueur(&(j->joueur));
    libererJeu(j);
}


void jeuClavier(Jeu *j, const char touche)
{
    switch (touche)
    {
    case 'g':
        joueurGauche(&(j->niveau));
        break;
    case 'd':
        joueurDroite(&(j->niveau));
        break;
    case 'h':
        joueurHaut(&(j->niveau));
        break;
    case 'b':
        joueurBas(&(j->niveau));
        break;
    }
}


int finNiveau(Niveau *n)
{
    int i, j;
    for (i = 0; i < n->dimx; i++)
    {
        for (j = 0; j < n->dimy; j++)
        {
            if (obtenirElementNiveau(n, i, j) == CIBLE)
            {
                return 0;
            }
        }
    }
    return 1;
}


int finJeu(Jeu *j)
{
    if ((j->niveau).num > NB_NIVEAUX) return 1;
    else return 0;
}

