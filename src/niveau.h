#ifndef _NIVEAU
#define _NIVEAU

/**
 * \file niveau.h
 * \author Steven Durrenmath
 */


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


#endif
