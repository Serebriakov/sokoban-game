#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "jeu.h"


void initialiserJeu(Jeu *j, const char *pseudo)
{
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
	modifierAvancement(&(j->joueur), niv);
}


void niveauSuivant(Jeu *j)
{
    changerNiveau(j, j->joueur.avancement + 1);
}


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
int joueurGauche(Niveau *n)
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
		return 0;
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
			return 1;
        }
        if (elem_gauche == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR_CIBLE);
			return 1;
        }
        if (elem_gauche == CAISSE && elem_gauche_gauche == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x-2, pos_joueur.y, CAISSE_OK);
			return 1;
        }
        if (elem_gauche == CAISSE && elem_gauche_gauche == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x-2, pos_joueur.y, CAISSE);
			return 1;
        }
        if (elem_gauche == CAISSE_OK && elem_gauche_gauche == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x-2, pos_joueur.y, CAISSE);
			return 1;
        }
        if (elem_gauche == CAISSE_OK && elem_gauche_gauche == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x-2, pos_joueur.y, CAISSE_OK);
			return 1;
        }
		else return 0;
    }

    if (obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y) == JOUEUR_CIBLE) // Le joueur est sur une cible
    {
        if (elem_gauche == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR);
			return 1;
        }
        if (elem_gauche == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR_CIBLE);
			return 1;
        }
        if (elem_gauche == CAISSE && elem_gauche_gauche == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x-2, pos_joueur.y, CAISSE_OK);
			return 1;
        }
        if (elem_gauche == CAISSE && elem_gauche_gauche == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x-2, pos_joueur.y, CAISSE);
			return 1;
        }
        if (elem_gauche == CAISSE_OK && elem_gauche_gauche == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x-2, pos_joueur.y, CAISSE);
			return 1;
        }
        if (elem_gauche == CAISSE_OK && elem_gauche_gauche == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x-1, pos_joueur.y, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x-2, pos_joueur.y, CAISSE_OK);
			return 1;
        }
		else return 0;
    }
	return 0;
}


// Procédure auxiliaire
int joueurDroite(Niveau *n)
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
		return 0;
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
			return 1;
        }
        if (elem_droite == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR_CIBLE);
			return 1;
        }
        if (elem_droite == CAISSE && elem_droite_droite == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x+2, pos_joueur.y, CAISSE_OK);
			return 1;
        }
        if (elem_droite == CAISSE && elem_droite_droite == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x+2, pos_joueur.y, CAISSE);
			return 1;
        }
        if (elem_droite == CAISSE_OK && elem_droite_droite == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x+2, pos_joueur.y, CAISSE);
			return 1;
        }
        if (elem_droite == CAISSE_OK && elem_droite_droite == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x+2, pos_joueur.y, CAISSE_OK);
			return 1;
        }
		else return 0;
    }

    if (obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y) == JOUEUR_CIBLE) // Le joueur est sur une cible
    {
        if (elem_droite == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR);
			return 1;
        }
        if (elem_droite == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR_CIBLE);
			return 1;
        }
        if (elem_droite == CAISSE && elem_droite_droite == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x+2, pos_joueur.y, CAISSE_OK);
			return 1;
        }
        if (elem_droite == CAISSE && elem_droite_droite == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x+2, pos_joueur.y, CAISSE);
			return 1;
        }
        if (elem_droite == CAISSE_OK && elem_droite_droite == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x+2, pos_joueur.y, CAISSE);
			return 1;
        }
        if (elem_droite == CAISSE_OK && elem_droite_droite == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x+1, pos_joueur.y, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x+2, pos_joueur.y, CAISSE_OK);
			return 1;
        }
		else return 0;
    }
	return 0;
}


// Procédure auxiliaire //
int joueurHaut(Niveau *n)
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
		return 0;
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
			return 1;
        }
        if (elem_haut == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR_CIBLE);
			return 1;
        }
        if (elem_haut == CAISSE && elem_haut_haut == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-2, CAISSE_OK);
			return 1;
        }
        if (elem_haut == CAISSE && elem_haut_haut == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-2, CAISSE);
			return 1;
        }
        if (elem_haut == CAISSE_OK && elem_haut_haut == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-2, CAISSE);
			return 1;
        }
        if (elem_haut == CAISSE_OK && elem_haut_haut == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-2, CAISSE_OK);
			return 1;
        }
		else return 0;
    }
    if (obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y) == JOUEUR_CIBLE) // Le joueur est sur une cible
    {
        if (elem_haut == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR);
			return 1;
        }
        if (elem_haut == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR_CIBLE);
			return 1;
        }
        if (elem_haut == CAISSE && elem_haut_haut == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-2, CAISSE_OK);
			return 1;
        }
        if (elem_haut == CAISSE && elem_haut_haut == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-2, CAISSE);
			return 1;
        }
        if (elem_haut == CAISSE_OK && elem_haut_haut == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-2, CAISSE);
			return 1;
        }
        if (elem_haut == CAISSE_OK && elem_haut_haut == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-1, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y-2, CAISSE_OK);
			return 1;
        }
		else return 0;
    }
	return 0;
}


// Procédure auxiliaire //
int joueurBas(Niveau *n)
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
		return 0;
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
			return 1;
        }
        if (elem_bas == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR_CIBLE);
			return 1;
        }
        if (elem_bas == CAISSE && elem_bas_bas == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+2, CAISSE_OK);
			return 1;
        }
        if (elem_bas == CAISSE && elem_bas_bas == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+2, CAISSE);
			return 1;
        }
        if (elem_bas == CAISSE_OK && elem_bas_bas == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+2, CAISSE);
			return 1;
        }
        if (elem_bas == CAISSE_OK && elem_bas_bas == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, VIDE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+2, CAISSE_OK);
			return 1;
        }
		else return 0;
    }

    if (obtenirElementNiveau(n, pos_joueur.x, pos_joueur.y) == JOUEUR_CIBLE) // Le joueur est sur une cible
    {
        if (elem_bas == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR);
			return 1;
        }
        if (elem_bas == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR_CIBLE);
			return 1;
        }
        if (elem_bas == CAISSE && elem_bas_bas == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+2, CAISSE_OK);
			return 1;
        }
        if (elem_bas == CAISSE && elem_bas_bas == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+2, CAISSE);
			return 1;
        }
        if (elem_bas == CAISSE_OK && elem_bas_bas == VIDE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+2, CAISSE);
			return 1;
        }
        if (elem_bas == CAISSE_OK && elem_bas_bas == CIBLE)
        {
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y, CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+1, JOUEUR_CIBLE);
            modifierElementNiveau(n, pos_joueur.x, pos_joueur.y+2, CAISSE_OK);
			return 1;
        }
		else return 0;
    }
	return 0;
}


void libererJeu(Jeu *j)
{
    libererNiveau(&(j->niveau));
}


void quitterJeu(Jeu *j)
{
	if (j->niveau.num <= nbNiveaux()) j->joueur.avancement = j->niveau.num;
    sauvegarderJoueur(&(j->joueur));
    libererJeu(j);
}


int jeuClavier(Jeu *j, const char touche)
{
    switch (touche)
    {
    case 'h':
        if(joueurHaut(&(j->niveau))) return 1;
		else return 0;
    case 'b':
        if(joueurBas(&(j->niveau))) return 1;
		else return 0;
    case 'g':
        if(joueurGauche(&(j->niveau))) return 1;
		else return 0;
    case 'd':
        if (joueurDroite(&(j->niveau))) return 1;
		else return 0;
    }
	return 0;
}


int finNiveau(Niveau *n)
{
    int i, j;
    for (i = 0; i < n->dimx; i++)
    {
        for (j = 0; j < n->dimy; j++)
        {
            if (obtenirElementNiveau(n, i, j) == CIBLE || obtenirElementNiveau(n, i, j) == JOUEUR_CIBLE)
            {
                return 0;
            }
        }
    }
    return 1;
}


int finJeu(Jeu *j)
{
    if ((j->niveau).num > nbNiveaux()) return 1;
    else return 0;
}

