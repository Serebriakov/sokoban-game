#ifndef _NIVEAU
#define _NIVEAU

/**
 * \file niveau.h
 * \author Steven Durrenmath
 */


#include "constantes.h"


 /** \struct Niveau */
 typedef struct
 {
    int num;
    int dimx;
    int dimy;
    int **tab;
 } Niveau;


/**
  * \fn void initialiserNiveau(Niveau *n, int dimx, int dimy)
  * \brief Initialise un niveau
  * \param[in, out] n Pointeur sur un niveau
  * \param[in] dimx Nombre de blocs en largeur
  * \param[in] dimy Nombre de blocs en hauteur
  */
void initialiserNiveau(Niveau *n, int dimx, int dimy);


/**
  * \fn int obtenirNumNiveau(const Niveau *n)
  * \param[in] n Pointeur sur un niveau
  * \return Retourne le numéro du niveau
  */
int obtenirNumNiveau(const Niveau *n);


/**
  * \fn void modifierNumNiveau(Niveau *n, int niv)
  * \brief Modifier le numéro du niveau
  * \param[in, out] n Pointeur sur un niveau
  * \param[in] niv Niveau
  */
void modifierNumNiveau(Niveau *n, int niv);


/**
  * \fn int obtenirDimXNiveau(const Niveau *n)
  * \param[in] n Pointeur sur un niveau
  * \return Retourne la dimension x du niveau
  */
int obtenirDimXNiveau(const Niveau *n);


/**
  * \fn int obtenirDimYNiveau(const Niveau *n)
  * \param[in] n Pointeur sur un niveau
  * \return Retourne la dimension y du niveau
  */
int obtenirDimYNiveau(const Niveau *n);


/**
 * \fn int obtenirElementNiveau(const Niveau *n, int x, int y)
 * \brief Retourne l'élément de coordonnées (x,y)
 * \param[in] n Pointeur sur un niveau
 * \param[in] x Première coordonnée
 * \param[in] y Deuxième coordonnée
 */
int obtenirElementNiveau(const Niveau *n, int x, int y);


/**
 * \fn void modifierElementNiveau(Niveau *n, int x, int y, int e)
 * \brief Modifie l'élément de coordonnées (x,y)
 * \param[in] n Pointeur sur un niveau
 * \param[in] x Première coordonnée
 * \param[in] y Deuxième coordonnée
 * \param[in] e Nouvel élément
 */
void modifierElementNiveau(Niveau *n, int x, int y, int e);


/**
 * \fn void libererNiveau(Niveau *n)
 * \brief Libère un niveau
 * \param[in, out] n Pointeur sur un niveau
 */
void libererNiveau(Niveau *n);


/**
 * \fn void testRegressionNiveau()
 * \brief Teste toutes les procédures du module Niveau
*/
void testRegressionNiveau();


#endif
