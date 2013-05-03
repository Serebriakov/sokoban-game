#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "fichiers.h"
#include "constantes.h"
#include "niveau.h"
#include "afficheTXT.h"


/*////////////////////////////////////////////////
// FONCTIONS DE GESTION DES FICHIERS DE NIVEAUX //
////////////////////////////////////////////////*/
void chargerNiveau(Niveau *n, int niv)
{
    int i, j;
    int dimx;
    int dimy;
    char fichier[30]; // Correspondra au nom du fichier de niveau
    FILE *fic = NULL;

    assert(niv <= NB_NIVEAUX); // Vérifie que le niveau existe
    n->num = niv; // Met à jour le numéro du niveau

    strcpy(fichier, "data/niveaux/");
    char niveau[3];
    sprintf(niveau, "%d", niv);
    strcat(fichier, niveau); // Le nom du fichier de niveau est de la forme "data/niveaux/xx.sok"
    strcat(fichier, ".sok");

    fic = fopen(fichier, "r");
    assert(fic != NULL);
    fscanf(fic, "%d %d ", &dimx, &dimy); // Récupère les dimensions du niveau qui sont écrites au début du fichier
    char ligneFichier[dimx*dimy+1]; // Contiendra les données du niveau
    fgets(ligneFichier, dimx*dimy+1, fic); // Les données du niveau sont stockées sur une seule ligne de taille dimx*dimy+1
    fclose(fic);

    libererNiveau(n); // Le niveau est une structure dynamique qui peut changer de taille. On commence par libérer l'espace alloué.
    initialiserNiveau(n, dimx, dimy); // Puis on réinitialise le niveau avec les nouvelles dimensions récupérées précédemment.


    // Recopie les données du niveau //
    for (i = 0; i < n->dimx; i++)
    {
        for (j = 0; j < n->dimy; j++)
        {
            switch(ligneFichier[i*dimx+j])
            {
            case '0':
                n->tab[j][i] = 0;
                break;
            case '1':
                n->tab[j][i] = 1;
                break;
            case '2':
                n->tab[j][i] = 2;
                break;
            case '3':
                n->tab[j][i] = 3;
                break;
            case '4':
                n->tab[j][i] = 4;
                break;
            case '5':
                n->tab[j][i] = 5;
                break;
            case '6':
                n->tab[j][i] = 6;
                break;
            }
        }
    }
}

void sauvegarderNiveau(const Niveau *n, const char *fichier)
{
    int i, j;
    FILE *fic = NULL;

    fic = fopen(fichier, "w"); // Ouvre le fichier en écriture et écrase les données existantes
    assert (fic != NULL);


    /* Recopie les dimensions du niveau */
    fprintf(fic, "%d ", n->dimx);
    fprintf(fic, "%d ", n->dimy);

    /* Recopie les données du niveau */
    for (i = 0 ; i < n->dimx ; i++)
    {
        for (j = 0 ; j < n->dimy ; j++)
        {
            fprintf(fic, "%d", n->tab[j][i]);
        }
    }
    fclose(fic);
}


/*////////////////////////////////////////////////
// FONCTIONS DE GESTION DES FICHIERS DE JOUEURS //
////////////////////////////////////////////////*/
void creerJoueur(Joueur *j, const char *pseudo)
{
    assert(strlen(pseudo) < 16);
    char fichier[36]; // Contiendra le nom du fichier joueur
    FILE *fic = NULL;

    strcpy(j->pseudo, pseudo);
    j->avancement = 1; // Le joueur débute au niveau 1

    strcpy(fichier, "data/joueurs/");
    strcat(fichier, j->pseudo); // Le fichier joueur est de la forme "data/joueurs/pseudo.sok"
    strcat(fichier, ".sok");

    fic = fopen(fichier, "wb"); // Ouverture du fichier joueur en mode écriture
    fwrite(j, sizeof(Joueur), 1, fic); // Écriture des ddnnées du joueur en un seul bloc
    fclose(fic);
}


void chargerJoueur(Joueur *j, const char *pseudo)
{
    char fichier[36]; // Contiendra le nom du fichier joueur
    FILE *fic = NULL;

    strcpy(fichier, "data/joueurs/");
    strcat(fichier, pseudo); // Le fichier joueur est de la forme "data/joueurs/pseudo.sok"
    strcat(fichier, ".sok");

    fic = fopen(fichier, "rb"); // Ouverture du fichier joueur en mode lecture
    fread(j, sizeof(Joueur), 1, fic); // Lecture des données du joueur en un seul bloc
    fclose(fic);
}


void sauvegarderJoueur(const Joueur *j)
{
    char fichier[36]; // Contiendra le nom du fichier joueur
    FILE *fic = NULL;

    strcpy(fichier, "data/joueurs/");
    strcat(fichier, j->pseudo); // Le fichier joueur est de la forme "data/joueurs/pseudo.sok"
    strcat(fichier, ".sok");

    fic = fopen(fichier, "a+b"); // Ouverture du fichier en mode écriture (sans écrasement)
    fseek(fic, 16, SEEK_SET); // Déplacement au 16eme octet, là où se trouve l'avancement du joueur
    fwrite(&(j->avancement), 4, 1, fic); // Écriture du nouvel avancement par dessus l'ancien
    fclose(fic);
}


void supprimerJoueur(Joueur* j)
{
    char fichier[36]; // Contiendra le nom du fichier joueur

    strcpy(fichier, "data/joueurs/");
    strcat(fichier, j->pseudo); // Le fichier joueur est de la forme "data/joueurs/pseudo.sok"
    strcat(fichier, ".sok");
    remove(fichier); // Suppression du fichier (sans confirmation)
}
