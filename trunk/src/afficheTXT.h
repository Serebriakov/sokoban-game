#ifndef _AFFICHETXT
#define _AFFICHETXT

/**
 * \file AfficheTXT.h
 * \brief Gestion de l'affichage texte
 * \author Steven Durrenmath
 */

#include "jeu.h"
#include "menu.h"
#include "joueur.h"
#include "niveau.h"


/**
 * \fn void afficherJoueurs
 * \brief Affiche le nom de tous les joueurs
 */
void afficherJoueurs();

/**
 * \fn void afficherMenu(const Menu *m)
 * \brief Affiche un menu
 */
void afficherMenu(const Menu *m);


/**
 * \fn void boucleMenu(Menu *m)
 * \brief Boucle événementielle du menu
 * \param[in, out] m Pointeur sur un menu
 */
void boucleMenu(Menu *m);


/**
 * \fn void afficherJeu(const Jeu *j)
 * \brief Affiche les données du jeu
 * \param[in] j Pointeur sur un jeu
 */
void afficherJeu(const Jeu *j);


/**
 * \fn void boucleJeu(Jeu *j)
 * \brief Boucle événementielle du jeu
 * \param[in, out] j Pointeur sur un jeu
 */
void boucleJeu(Jeu *j);


#endif
