#ifndef _NIVEAU
#define _NIVEAU

/**

 \file Niveau.h
 \author Steven Durrenmath

 */


#define BLOCS_LARGEUR 15
#define BLOCS_HAUTEUR 15


 /** \struct Niveau */
 typedef struct
 {
    int tab[BLOCS_LARGEUR][BLOCS_HAUTEUR];
 } Niveau;


/**

 \fn void chargerNiveau(Niveau *n, const char *fichier)
 \brief Charge un niveau
 \param[in, out] n Pointe sur le niveau à charger
 \param[in] fichier Nom du fichier à charger

 */
void chargerNiveau(Niveau *n, const char *fichier);


/**

 \fn void sauvegarderNiveau(const Niveau *n, const char *fichier)
 \brief Sauvegarde un niveau
 \param[in] n Pointe sur le niveau à sauvegarder
 \param[in] fichier Nom du fichier dans lequel le niveau est sauvegardé

 */
void sauvegarderNiveau(const Niveau *n, const char *fichier);


#endif
