#ifndef _NIVEAU
#define _NIVEAU

/**

 \file Niveau.h
 \author Steven Durrenmath

 */


 /** \struct Niveau */
 typedef struct
 {
    int num;
    int dimx; // Largeur = nombre de colonnes
    int dimy; // Hauteur = nombre de lignes
    int **tab;
 } Niveau;


enum {JOUEUR, VIDE, CIBLE, CAISSE, CAISSE_OK, MUR};


 /**

  \fn void initialiserNiveau(Niveau *n, int dimx, int dimy)
  \brief Initialise un niveau
  \param[in, out] n Pointe sur le niveau à initialiser
  \param[in] dimx Nombre de blocs en largeur
  \param[in] dimy Nombre de blocs en hauteur

  */
void initialiserNiveau(Niveau *n, int dimx, int dimy);


/**

 \fn void chargerNiveau(Niveau *n, const char *fichier)
 \brief Charge un niveau
 \param[in, out] n Pointe sur un niveau
 \param[in] niv Niveau à charger

 */
void chargerNiveau(Niveau *n, const char* niv);


/**

 \fn void sauvegarderNiveau(const Niveau *n, const char *fichier)
 \brief Sauvegarde un niveau
 \param[in] n Pointe sur le niveau à sauvegarder
 \param[in] fichier Nom du fichier dans lequel le niveau est sauvegardé

 */
void sauvegarderNiveau(const Niveau *n, const char *fichier);


/**

 \fn int obtenirElementNiveau(const Niveau *n, int x, int y)
 \brief Retourne l'élément de coordonnées (x,y)
 \param[in] n Niveau
 \param[in] x Première coordonnée
 \param[in] y Deuxième coordonnée

 */
int obtenirElementNiveau(const Niveau *n, int x, int y);


/**

 \fn void modifierElementNiveau(const Niveau *n, int x, int y, int e)
 \brief Modifie l'élément de coordonnées (x,y)
 \param[in] n Niveau
 \param[in] x Première coordonnée
 \param[in] y Deuxième coordonnée
 \param[in] e Nouvel élément$

 */
void modifierElementNiveau(const Niveau *n, int x, int y, int e);


/**

 \fn void libererNiveau(Niveau *n)
 \brief Libère un niveau
 \param[in, out] n Pointe sur le niveau à libérer

 */
void libererNiveau(Niveau *n);


#endif
