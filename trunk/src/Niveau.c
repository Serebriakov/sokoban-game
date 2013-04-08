#include <stdlib.h>
#include <stdio.h>

#include "Niveau.h"


void chargerNiveau(Niveau *n, const char *fichier)
{
    FILE *fic = fopen(fichier, "r");
    char ligneFichier[BLOCS_LARGEUR*BLOCS_HAUTEUR+1];
    fgets(ligneFichier, BLOCS_LARGEUR*BLOCS_HAUTEUR+1, fic);
    fclose(fic);
    int i, j;
    for (i = 0; i < BLOCS_LARGEUR; i++)
    {
        for (j = 0; j < BLOCS_HAUTEUR; j++)
        {
            switch(ligneFichier[i*BLOCS_LARGEUR+j])
            {
            case '0': // Joueur
                n->tab[j][i] = 0;
                break;
            case '1': // Cible
                n->tab[j][i] = 1;
                break;
            case '2': // Caisse
                n->tab[j][i] = 2;
                break;
            case '3': // Mur
                n->tab[j][i] = 3;
                break;
            case '4': // Elem4
                n->tab[j][i] = 4;
                break;
            case '5': // Elem5
                n->tab[j][i] = 5;
                break;
            case '6': // Elem6
                n->tab[j][i] = 6;
                break;
            case '7': // Elem7
                n->tab[j][i] = 7;
                break;
            case '8': // Elem8
                n->tab[j][i] = 8;
                break;
            case '9': // Elem9
                n->tab[j][i] = 9;
                break;
            }
        }
    }
}


void sauvegarderNiveau(const Niveau *n, const char *fichier)
{
    FILE *fic = fopen(fichier, "w");
    int i, j;
    for (i = 0 ; i < BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < BLOCS_HAUTEUR ; j++)
        {
            fprintf(fic, "%d", n->tab[j][i]);
        }
    }
    fclose(fic);
}
