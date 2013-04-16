#include <stdio.h>
#include <string.h>

#include "Jeu.h"


void initialiserJeu(Jeu *j, const char *pseudo)
{
    creerJoueur(&(j->joueur), pseudo);
    initialiserNiveau(&(j->niveau), 1, 1);
    chargerNiveau(&(j->niveau), "1");
}


void chargerJeu(Jeu *j, const char *pseudo, const char *niveau)
{
    chargerJoueur(&(j->joueur), pseudo);
    initialiserNiveau(&(j->niveau), 1, 1);
    chargerNiveau(&(j->niveau), niveau);
}


void changerNiveau(Jeu *j, const char *niv)
{
    chargerNiveau(&(j->niveau), niv);
}


void niveauSuivant(Jeu *j)
{
    char suivant[3];
    sprintf(suivant, "%d", (j->niveau).num + 1);
    changerNiveau(j, suivant);
}


Position obtenirPositionJoueur(const Niveau *n)
{
    int x, y;
    Position pos;
    for (x = 0; x < n->dimx; x++)
    {
        for (y = 0; y < n->dimy; y++)
        {
            if (obtenirElementNiveau(n, x, y) == JOUEUR)
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


void joueurGauche(Niveau *n)
{
    Position pos_joueur = obtenirPositionJoueur(n);

    int elem_gauche; // On regarde l'élément à gauche du joueur
    if (pos_joueur.x-1 >= 0)
    {
        elem_gauche = obtenirElementNiveau(n, pos_joueur.x-1, pos_joueur.y);
    }
    else
    {
        elem_gauche = MUR;
    }

    int elem_gauche_gauche; // On regarde également l'élément encore à gauche
    if (pos_joueur.x-2 >= 0)
    {
        elem_gauche_gauche = obtenirElementNiveau(n, pos_joueur.x-2, pos_joueur.y);
    }
    else
    {
        elem_gauche_gauche = MUR;
    }

    // On déplace le joueur et éventuellement une caisse (déjà sur une case cible ou non)
    if (elem_gauche == VIDE)
    {
        modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
        modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR);
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


void joueurDroite(Niveau *n)
{
    Position pos_joueur = obtenirPositionJoueur(n);

    int elem_droite; // On regarde l'élément à droite du joueur
    if (pos_joueur.x+1 < n->dimx)
    {
        elem_droite = obtenirElementNiveau(n, pos_joueur.x+1, pos_joueur.y);
    }
    else
    {
        elem_droite = MUR;
    }

    int elem_droite_droite; // On regarde également l'élément encore à droite
    if (pos_joueur.x+2 < n->dimx)
    {
        elem_droite_droite = obtenirElementNiveau(n, pos_joueur.x+2, pos_joueur.y);
    }
    else
    {
        elem_droite_droite = MUR;
    }

    // On déplace le joueur et éventuellement une caisse (déjà sur une case cible ou non)
    if (elem_droite == VIDE)
    {
        modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
        modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR);
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


void joueurHaut(Niveau *n)
{
    Position pos_joueur = obtenirPositionJoueur(n);

    int elem_haut; // On regarde l'élément en haut du joueur
    if (pos_joueur.y-1 >= 0)
    {
        elem_haut = obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y-1);
    }
    else
    {
        elem_haut = MUR;
    }

    int elem_haut_haut; // On regarde également l'élément encore en haut
    if (pos_joueur.y-2 >= 0)
    {
        elem_haut_haut = obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y-2);
    }
    else
    {
        elem_haut = MUR;
    }

    // On déplace le joueur et éventuellement une caisse (déjà sur une case cible ou non)
    if (elem_haut == VIDE)
    {
        modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
        modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR);
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


void joueurBas(Niveau *n)
{
    Position pos_joueur = obtenirPositionJoueur(n);

    int elem_bas; // On regarde l'élément en bas du joueur
    if (pos_joueur.y+1 < n->dimy)
    {
        elem_bas = obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y+1);
    }
    else
    {
        elem_bas = MUR;
    }

    int elem_bas_bas; // On regarde également l'élément encore en bas
    if (pos_joueur.y+2 < n->dimy)
    {
        elem_bas_bas = obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y+2);
    }
    else
    {
        elem_bas_bas = MUR;
    }

    // On déplace le joueur et éventuellement une caisse (déjà sur une case cible ou non)
    if (elem_bas == VIDE)
    {
        modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
        modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR);
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


void libererJeu(Jeu *j)
{
    libererNiveau(&(j->niveau));
}


void quitterJeu(Jeu *j)
{
    modifierAvancement(&(j->joueur), (j->niveau).num);
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
