#ifndef _AFFICHETXT
#define _AFFICHETXT

/**
 * \file afficheTXT.h
 * \brief Gestion de l'affichage texte
 * \author Steven Durrenmath
 */

#include "jeu.h"
#include "menu.h"


/*////////////////////
// AFFICHAGE DU JEU //
////////////////////*/


/**
 * \fn void afficherJeu(const Jeu *j)
 * \brief Affiche le jeu (= niveau + numéro de niveau + pseudo du joueur)
 * \param[in] j Pointeur sur un jeu
 */
void afficherJeu(const Jeu *j);


/**
 * \fn void boucleJeu(Jeu *j)
 * \brief Boucle événementielle du jeu
 * \param[in, out] j Pointeur sur un jeu
 */
void boucleJeu(Jeu *j);



/*/////////////////////
// AFFICHAGE DU MENU //
/////////////////////*/


/**
 * \fn void nouvellePartie()
 * \brief Demande au joueur son pseudo et lance une nouvelle partie
 */
void nouvellePartie();


/**
 * \fn void chargerPartie()
 * \brief Affiche les parties existantes, demande au joueur de choisir une partie, et charge la partie
 */
void chargerPartie();


/**
 * \fn void boucleMenu(Menu *m)
 * \brief Boucle événementielle du menu
 * \param[in, out] m Pointeur sur un menu
 */
void boucleMenu(Menu *m);


#endif
