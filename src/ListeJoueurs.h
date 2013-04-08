#ifndef _LISTEJOUEURS
#define _LISTEJOUEURS

/**

 \file ListeJoueurs.h
 \brief Liste doublement chaînée de joueurs
 \author Steven Durrenmath

 */


#include "Joueur.h"


/** \struct CelluleJoueurs */
struct sCelluleJoueur
{
    Joueur info;
    struct sCelluleJoueur * precedent;
    struct sCelluleJoueur * suivant;
};
typedef struct sCelluleJoueur CelluleJoueur;



/** \struct ListeJoueurs */
typedef struct
{
    CelluleJoueur * prem;
    CelluleJoueur * last;
} ListeJoueurs;


/**

 \fn void initialiserListe(ListeJoueurs * l)
 \brief Initialise une liste de joueurs l
 \param[in, out] l Pointe sur la liste à initialiser

 */
void initialiserListe(ListeJoueurs * l);


/**

 \fn int estVideListe(const ListeJoueurs * l)
 \brief Teste si la liste de joueurs est vide
 \param[in] l Liste de joueurs

 */
int estVideListe(const ListeJoueurs * l);


/**

 \fn unsigned int nbElementsListe(const ListeJoueurs * l)
 \brief Donne le nombre d'élements de la liste de joueurs
 \param[in] l Liste de joueurs

 */
unsigned int nbElementsListe(const ListeJoueurs * l);


/**

 \fn Joueur iemeElementListe(const ListeJoueurs * l, unsigned int i)
 \brief Permet d'obtenir les données du i-ème joueur de la liste
 \param[in] l Liste de joueurs
 \param[in] i Position du joueur

 */
Joueur iemeElementListe(const ListeJoueurs * l, unsigned int i);


/**

 \fn void modifierIemeElementListe(const ListeJoueurs * l, unsigned int i, Joueur j)
 \brief Modifie le i-ème joueur de la liste
 \param[in] l Liste de joueurs
 \param[in] i Position du joueur
 \param[in] j Données du nouveau Joueur

 */
void modifierIemeElementListe(const ListeJoueurs * l, unsigned int i, const Joueur j);


/**

 \fn void ajouterEnTeteListe(Joueur j, ListeJoueurs * l)
 \brief Ajoute un joueur en tête de liste
 \param[in] j Données du joueur à ajouter
 \param[in, out] l Liste de joueurs

 */
void ajouterEnTeteListe(const Joueur j, ListeJoueurs * l);


/**

 \fn void ajouterEnQueueListe(const Joueur j, ListeJoueurs * l)
 \brief Ajoute un joueur en queue de liste
 \param[in] j Données du joueur à ajouter
 \param[in, out] l Liste de joueurs

 */
void ajouterEnQueueListe(const Joueur j, ListeJoueurs * l);


/**

 \fn void supprimerTeteListe(ListeJoueurs * l)
 \brief Supprime la tête de liste
 \param[in, out] l Liste de joueurs

 */
void supprimerTeteListe(ListeJoueurs * l);


/**

 \fn void viderListe(ListeJoueurs * l)
 \brief Vide la liste
 \param[in, out] l Liste de joueurs

 */
void viderListe(ListeJoueurs * l);


/**

 \fn void testamentListe(ListeJoueurs * l)
 \brief Libère la liste
 \param[in, out] l Liste de joueurs

 */
void testamentListe(ListeJoueurs * l);


/**

 \fn void affecterListe(ListeJoueurs * l1, const ListeJoueurs * l2)
 \brief Affecte la liste l2 dans la liste l1
 \param[in, out] l1 Liste de joueurs destination
 \param[in] l2 Liste de joueurs source

 */
void affecterListe(ListeJoueurs * l1, const ListeJoueurs * l2);


/**

 \fn int rechercherElementListe(const Joueur j, const ListeJoueurs * l)
 \brief Donne la position du joueur dans la liste
 \param[in] j Joueur
 \param[in] l Liste de joueurs

 */
int rechercherElementListe(const Joueur j, const ListeJoueurs *l);


/**

 \fn void insererElementListe(const Joueur j, ListeJoueurs * l, unsigned int position)
 \brief Insère le joueur en i-ème position dans la liste
 \param[in] j Joueur
 \param[in] l Liste de joueurs
 \param[in] position Position

 */
void insererElementListe(const Joueur j, ListeJoueurs * l, unsigned int position);


#endif
