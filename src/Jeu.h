#ifndef _JEU
#define _JEU


/**

 \file Jeu.h
 \author Steven Durrenmath

 */


#include "Joueur.h"
#include "Niveau.h"

#define NB_NIVEAUX 5


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

 \fn initialiserJeu(Jeu *j)
 \brief Initialise un jeu
 \param[in, out] j Pointe sur le jeu à initialiser
 \param[in] pseudo Nom du joueur

 */
void initialiserJeu(Jeu *j, const char *pseudo);


/**

 \fn libereJeu(Jeu *j)
 \brief Libère un jeu
 \param[in, out] j Pointe sur le jeu à libérer

 */
void libererJeu(Jeu *j);



#endif
