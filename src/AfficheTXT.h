#ifndef _AFFICHETXT
#define _AFFICHETXT

/**

 \file AfficheTXT.h
 \author Steven Durrenmath

 */

#include "Jeu.h"
#include "Menu.h"

/**

 \fn void afficherJoueurs
 \brief Affiche le nom de tous les joueurs

 */
void afficherJoueurs();


/**

 \fn void boucleJeu(Jeu *j)
 \brief Boucle événementielle du jeu

 */
void boucleJeu(Jeu *j);


/**

 \fn void boucleMenu(Menu *m)
 \brief Boucle événementielle du menu

 */
void boucleMenu(Menu *m);


#endif
