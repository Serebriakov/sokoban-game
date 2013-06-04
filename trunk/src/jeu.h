#ifndef _JEU
#define _JEU

/**
 * \file jeu.h
 * \author Steven Durrenmath
 */

#include "joueur.h"
#include "niveau.h"
#include "fichiers.h"


/** \struct Jeu */
typedef struct
{
    Joueur joueur;
    Niveau niveau;
} Jeu;


/** 
 * \struct Position
 * \brief Contiendra la position du joueur
 */
typedef struct
{
    int x;
    int y;
} Position;


/**
 * \fn void initialiserJeu(Jeu *j, const char *pseudo)
 * \brief Initialise un jeu
 * \param[in, out] j Pointeur sur un jeu
 * \param[in] pseudo Pseudo du joueur
 */
void initialiserJeu(Jeu *j, const char *pseudo);


/**
 * \fn void chargerJeu(Jeu *j, const char *pseudo)
 * \brief Permet de charger la partie d'un joueur
 * \param[in, out] j Pointeur sur un jeu
 * \param[in] pseudo Pseudo du joueur
 */
void chargerJeu(Jeu *j, const char *pseudo);


/**
 * \fn void niveauSuivant(Jeu *j)
 * \brief Permet de passer au niveau suivant
 * \param[in, out] j Pointeur sur un jeu
 */
void niveauSuivant(Jeu *j);


/**
 * \fn void libererJeu(Jeu *j)
 * \brief Libère un jeu
 * \param[in, out] j Pointeur sur un jeu
 */
void libererJeu(Jeu *j);


/**
 * \fn void quitterJeu(Jeu *j)
 * \brief Quitte le jeu en sauvegardant
 * \param[in, out] j Pointeur sur un jeu
 */
void quitterJeu(Jeu *j);


/**
 * \fn Position obtenirPositionJoueur(const Niveau *n)
 * \brief Permet d'obtenir la position du joueur
 * \param[in] n Pointeur sur un niveau
 */
Position obtenirPositionJoueur(const Niveau *n);


/**
 * \fn void jeuClavier(Jeu *j, const char touche)
 * \brief Gère les déplacements du joueur au clavier
 * \param[in, out] j Pointeur sur un jeu
 * \param[in] touche Touche du clavier
 * \return Retourne 1 si le joueur a pu se déplacer, 0 sinon
 */
int jeuClavier(Jeu *j, const char touche);


/**
 * \fn int finNiveau(Niveau *n)
 * \brief Teste si le niveau est terminé
 * \param[in, out] n Pointeur sur un niveau
 */
int finNiveau(Niveau *n);


/**
 * \fn int finJeu(Jeu *j)
 * \brief Teste si le jeu est terminé
 * \param[in, out] j Pointeur sur un jeu
 */
int finJeu(Jeu *j);


#endif
