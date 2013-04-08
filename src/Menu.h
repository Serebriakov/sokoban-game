#ifndef _MENU
#define _MENU

/**

 \file Menu.h
 \author Steven Durrenmath

 */


typedef void (*MenuFonction)();


/** \struct MenuLigne */
typedef struct
{
    char texte[64];
    MenuFonction commande;
} MenuLigne;


/** \struct Menu */
typedef struct
{
    MenuLigne lignes[32];
    int nb_lignes;
} Menu;


/**

 \fn void menuInit(Menu* m)
 \brief Initialise un menu

 \param[in, out] m Pointeur sur un menu

*/
void menuInit(Menu* m);


/**

 \fn void menuAjouterLigne(Menu* m, char texte[64], MenuFonction fonction);
 \brief Ajoute une ligne dans un menu

 \param[in, out] m Pointeur sur un menu
 \param[in] texte Nom de la nouvelle ligne de menu
 \param[in] fonction Fonction associée à la ligne

*/
void menuAjouterLigne(Menu* m, char* texte, MenuFonction fonction);


/**

 \fn void menuLibere(Menu* m)
 \brief Libère un menu

 \param[in, out] m Pointeur sur un menu

*/
void menuLibere(Menu* m);



#endif
