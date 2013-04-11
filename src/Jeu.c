#include <stdio.h>
#include <string.h>
#include "Jeu.h"
#include "Joueur.h"
#include "Niveau.h"


void initialiserJeu(Jeu *j, const char *pseudo)
{
    creerJoueur(&(j->joueur), pseudo);
    initialiserNiveau(&(j->niveau), 1, 1);
    chargerNiveau(&(j->niveau), "1");
}


void chargerJeu(Jeu *j, const char *pseudo, const char *niveau)
{
    chargerJoueur(&(j->joueur), pseudo);
    chargerNiveau(&(j->niveau), niveau);
}


void changerJoueur(Jeu *j, Joueur p)
{
    j->joueur = p;
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


Position obtenirPositionJoueur(const Jeu *j)
{
    int x, y;
    Position pos;
    for (x = 0; x < (j->niveau).dimx; x++)
    {
        for (y = 0; y < (j->niveau).dimy; y++)
        {
            if ((j->niveau).tab[y][x] == 0)
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

}


void joueurDroite(Niveau *n)
{
 // A ECRIRE
}


void joueurHaut(Niveau *n)
{
 // A ECRIRE
}


void joueurBas(Niveau *n)
{
 // A ECRIRE
}


void quitterJeu(Jeu *j)
{
 // A ECRIRE
}


void jeuClavier(Jeu *j, const char touche)
{
    switch (touche)
    {
        case 'g':
            joueurGauche(&(j->niveau));
        case 'd':
            joueurDroite(&(j->niveau));
        case 'h':
            joueurHaut(&(j->niveau));
        case 'b':
            joueurBas(&(j->niveau));
        case 'q':
            quitterJeu(j);
    }
}


int finNiveau(Jeu *j)
{
    return 0; // A ECRIRE
}


int finJeu(Jeu *j)
{
    if ((j->niveau).num > NB_NIVEAUX) return 1;
    else return 0;
}


void libererJeu(Jeu *j)
{
    libererNiveau(&(j->niveau));
}
