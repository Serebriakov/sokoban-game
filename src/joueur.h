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
} Joueur;


/**
 * \fn int obtenirAvancement(Joueur *j)
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
/* ATTENTION, cela ne modifie pas le fichier  //
// joueur donc ne sauvegarde pas ses données. */

#endif
