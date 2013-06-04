#ifndef _JOUEUR
#define _JOUEUR

/**
 * \file joueur.h
 * \author Steven Durrenmath
 */


/** \struct Joueur */
typedef struct
{
    char pseudo[16];
    int avancement;
	int scores[20];
} Joueur;


/**
 * \fn int obtenirAvancement(const Joueur *j)
 * \brief Retourne le prochain niveau à résoudre
 * \param[in] j Pointeur sur un joueur
 */
int obtenirAvancement(const Joueur *j);


/**
 * \fn void modifierAvancement(Joueur *j, int niv)
 * \brief Met à jour l'avancement du joueur dans le jeu
 * \param[in, out] j Pointeur sur un joueur
 * \param[in] niv Dernier niveau résolu
 */
void modifierAvancement(Joueur *j, int niv);


/**
 * \fn int obtenirScore(const Joueur *j, int niv)
 * \param[in] j Pointeur sur un joueur
 * \param[in] niv Niveau
 * \return Retourne le score du joueur à un certain niveau
 */
int obtenirScore(const Joueur *j, int niv);


/**
 * \fn void modifierScore(Joueur *j, int niv, int score)
 * \brief Modifie le score du joueur à un certain niveau
 * \param[in] j Pointeur sur un joueur
 * \param[in] niv Niveau
 * \param[in] score Score
 */
void modifierScore(Joueur *j, int niv, int score);


/**
 * \fn void testRegressionJoueur()
 * \brief Teste toutes les procédures du module Joueur
*/
void testRegressionJoueur();


#endif
