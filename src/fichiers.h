/**
 * \file fichiers.h
 * \brief Gestion de fichiers.
 * \author Steven Durrenmath

 * Fonctions gérant la lecture et l'écriture de fichiers de joueurs et de niveaux.
 */

#include "niveau.h"
#include "joueur.h"


/*////////////////////////////////////////////////
// FONCTIONS DE GESTION DES FICHIERS DE NIVEAUX //
////////////////////////////////////////////////*/

/**
 * \fn void chargerNiveau(Niveau *n, int niv)
 * \brief Charge un niveau
 * \param[in, out] n Pointeur sur un niveau
 * \param[in] niv Numéro du niveau à charger
 */
void chargerNiveau(Niveau *n, int niv);


/**
 * \fn void sauvegarderNiveau(const Niveau *n, const char *fichier)
 * \brief Sauvegarde un niveau
 * \param[in] n Pointeur sur un niveau
 * \param[in] fichier Nom du fichier dans lequel le niveau est sauvegardé
 */
void sauvegarderNiveau(const Niveau *n, const char *fichier);


/**
 * \fn int nbNiveaux()
 * \brief Compte le nombre de niveaux
 */
int nbNiveaux();



/*////////////////////////////////////////////////
// FONCTIONS DE GESTION DES FICHIERS DE JOUEURS //
////////////////////////////////////////////////*/

/**
 * \fn int creerJoueur(Joueur *j, const char *pseudo);
 * \brief Créer un nouveau joueur
 * \param[in, out] j Pointeur sur un joueur
 * \param[in] pseudo Pseudo du joueur à créer
 * \return Retourne -1 si le max de joueurs a déjà été créé, ou 0 si un joueur a pu être créé.
 */
int creerJoueur(Joueur *j, const char *pseudo);


/**
 * \fn void chargerJoueur(Joueur *j, const char *pseudo)
 * \brief Charge les données d'un joueur
 * \param[in, out] j Pointeur sur un joueur
 * \param[in] pseudo Pseudo du joueur à charger
 */
void chargerJoueur(Joueur *j, const char *pseudo);


/**
 * \fn void sauvegarderJoueur(const Joueur *j)
 * \brief Sauvegarde les données d'un joueur
 * \param[in] j Pointeur sur un joueur
 */
void sauvegarderJoueur(const Joueur *j);


/**
 * \fn supprimerJoueur(const char *pseudo)
 * \brief Supprime un joueur
 * \param[in] pseudo Pseudo du joueur à supprimer
 */
void supprimerJoueur(const char *pseudo);
