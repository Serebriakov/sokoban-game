#ifndef _AFFICHESDL
#define _AFFICHESDL

/**
 * \file afficheSDL.h
 * \brief Gestion de l'affichage SDL
 * \author Steven Durrenmath
 */


#include "jeu.h"


/*//////////////////////////////
////////// BOUCLE JEU //////////
//////////////////////////////*/


/**
 * \fn void afficherJeu(Jeu *j, SDL_Surface **sprites, int direction_joueur, int nb_mvmts, SDL_Surface *ecran)
 * \brief Affiche le jeu (= niveau + numéro de niveau + nombre de mouvements)
 * \param[in, out] j Pointeur sur un jeu
 * \param[in, out] sprites Pointe sur le tableau des sprites à afficher
 * \param[in] direction_joueur Direction du joueur à afficher
 * \param[in] nb_mvmts Nombre de mouvements à afficher
 * \param[in, out] ecran Ecran d'affichage
 */
void afficherJeu(Jeu *j, SDL_Surface **sprites, int direction_joueur, int nb_mvmts, SDL_Surface *ecran);


/**
 * \fn void boucleJeu(Jeu *j, SDL_Surface *ecran)
 * \brief Boucle événementielle du jeu
 * \param[in, out] j Pointeur sur un jeu
 * \param[in, out] ecran Ecran d'affichage
 */
void boucleJeu(Jeu *j, SDL_Surface *ecran);



/*///////////////////////////////
////////// BOUCLE MENU //////////
///////////////////////////////*/


/**
 * \fn void nouvellePartie(SDL_Surface *ecran)
 * \brief Demande à l'utilisateur de saisir un pseudo et lance une nouvelle partie
 * \param[in, out] ecran Ecran d'affichage
 */
void nouvellePartie(SDL_Surface *ecran);


/**
 * \fn void chargerPartie(SDL_Surface *ecran)
 * \brief Affiche les parties existantes et demande à l'utilisateur quelle partie il veut continuer, puis charge la partie
 * \param[in, out] ecran Ecran d'affichage
 */
void chargerPartie(SDL_Surface *ecran);


/**
 * \fn void editerNiveau(SDL_Surface *ecran)
 * \brief Démarre l'éditeur de niveau
 * \param[in, out] ecran Ecran d'affichage
 */
void editerNiveau(SDL_Surface *ecran);


/**
 * \fn void consulterScores(SDL_Surface *ecran)
 * \brief Affiche les meilleurs scores par niveau avec le joueur qui l'a réalisé
 * \param[in, out] ecran Ecran d'affichage
 */
void consulterScores(SDL_Surface *ecran);


/**
 * \fn void boucleMenu(SDL_Surface *ecran)
 * \brief Boucle événementielle du menu
 * \param[in, out] ecran Ecran d'affichage
 */
void boucleMenu(SDL_Surface *ecran);


#endif
