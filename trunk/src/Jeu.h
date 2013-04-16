#ifndef _JEU
#define _JEU


/**

 \file Jeu.h
 \author Steven Durrenmath

 */


#include "Joueur.h"
#include "Niveau.h"

#define NB_NIVEAUX 1


/** \struct Jeu */
typedef struct
{
    Joueur joueur;
    Niveau niveau;
} Jeu;


/** \struct Position */
typedef struct
{
    int x;
    int y;
} Position;


/**

 \fn void initialiserJeu(Jeu *j, const char *pseudo)
 \brief Initialise un jeu
 \param[in, out] j Pointe sur le jeu à initialiser
 \param[in] pseudo Nom du joueur

 */
void initialiserJeu(Jeu *j, const char *pseudo);


/**

 \fn void chargerJeu(Jeu *j, const char *pseudo, const char *niveau)
 \brief Charge une partie dans le jeu
 \param[in, out] j Pointe sur le jeu à charger
 \param[in] pseudo Pseudo du joueur (nom de la partie)
 \param[in] niveau Niveau à charger dans le jeu

 */
void chargerJeu(Jeu *j, const char *pseudo, const char *niveau);


/**

 \fn void niveauSuivant(Jeu *j)
 \brief Permet de passer au niveau suivant
 \param[in, out] j Pointe sur le jeu

 */
void niveauSuivant(Jeu *j);


/**

 \fn void libererJeu(Jeu *j)
 \brief Libère un jeu
 \param[in, out] j Pointe sur le jeu à libérer

 */
void libererJeu(Jeu *j);


/**

 \fn void quitterJeu(Jeu *j)
 \brief Quitte le jeu en sauvegardant
 \param[in, out] Pointe sur le jeu

 */
void quitterJeu(Jeu *j);


/**

 \fn void jeuClavier(Jeu *j, const char touche)
 \brief Gère les déplacements du joueur au clavier
 \param[in, out] j Pointe sur le jeu à gérer
 \param[in] touche Touche du clavier

 */
void jeuClavier(Jeu *j, const char touche);


/**

 \fn int finNiveau(Niveau *n)
 \brief Teste si le niveau est terminé
 \param[in, out] n Pointe sur le niveau à tester

 */
int finNiveau(Niveau *n);


/**

 \fn int finJeu(Jeu *j)
 \brief Teste si le jeu est terminé
 \param[in, out] j Pointe sur le jeu à tester

 */
int finJeu(Jeu *j);


#endif
