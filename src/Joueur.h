#ifndef _JOUEUR
#define _JOUEUR


/**

 \file Joueur.h
 \author Steven Durrenmath

 */


/** \struct Joueur */
typedef struct
{
    char pseudo[16];
    int avancement;
} Joueur;


/**

 \fn void creerJoueur(Joueur* j, const char* pseudo);
 \brief Créer un nouveau joueur
 \param[in, out] j Pointe sur le joueur à créer
 \param[in] pseudo Pseudo du joueur à créer

 */
void creerJoueur(Joueur* j, const char* pseudo);


/**

 \fn void chargerJoueur(Joueur* j, const char* pseudo)
 \brief Charge les données d'un joueur
 \param[in, out] j Pointe sur le joueur à charger
 \param[in] pseudo Pseudo du joueur à charger

 */
void chargerJoueur(Joueur* j, const char* pseudo);


/**

 \fn char* obtenirPseudo(Joueur* j)
 \brief Retourne le pseudo du joueur
 \param[in] j Joueur

 */
char* obtenirPseudo(Joueur* j);


/**

 \fn int obtenirAvancement(Joueur* j)
 \brief Retourne le prochain niveau à résoudre
 \param[in] j Joueur

 */
int obtenirAvancement(Joueur* j);


/**

 \fn void modifierAvancement(Joueur* j, int niv)
 \brief Met à jour l'avancement du joueur dans le jeu
 \param[in, out] j Pointe sur le joueur à modifier
 \param[in] niv Dernier niveau résolu

 */
void modifierAvancement(Joueur* j, int niv);


/**

 \fn supprimerJoueur(Joueur* j)
 \brief Supprime le joueur
 \param[in, out] j Pointe sur le joueur à supprimer

 */
void supprimerJoueur(Joueur* j);


#endif
