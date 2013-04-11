#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "Joueur.h"


void creerJoueur(Joueur* j, const char* pseudo)
{
    assert(strlen(pseudo) < 16);
    strcpy(j->pseudo, pseudo);
    j->avancement = 1;

    /* Sauvegarde des données du joueur */
    char fichier[36];
    strcpy(fichier, "../data/joueurs/");
    strcat(fichier, j->pseudo);
    strcat(fichier, ".sok");
    FILE* fic = fopen(fichier, "wb");
    fwrite(j, sizeof(Joueur), 1, fic);
    fclose(fic);
}


void chargerJoueur(Joueur* j, const char* pseudo)
{
    char fichier[36];
    strcpy(fichier, "../data/joueurs/");
    strcat(fichier, pseudo);
    strcat(fichier, ".sok");
    FILE* fic = fopen(fichier, "rb");
    fread(j, sizeof(Joueur), 1, fic);
    fclose(fic);
}


int egaliteJoueur(const Joueur j1, const Joueur j2)
{
    if (strcmp(j1.pseudo, j2.pseudo))
    {
        return 1;
    }
    return 0;
}


char* obtenirPseudo(Joueur* j)
{
    return j->pseudo;
}


int obtenirAvancement(Joueur* j)
{
    return j->avancement;
}


void modifierAvancement(Joueur* j, int niv)
{
    j->avancement = niv;

    /* Sauvegarde des données du joueur */
    char fichier[36];
    strcpy(fichier, "../data/joueurs");
    strcat(fichier, j->pseudo);
    strcat(fichier, ".sok");
    FILE* fic = fopen(fichier, "a+b");
    fseek(fic, 16, SEEK_SET);
    fwrite(&j->avancement, 4, 1, fic);
    fclose(fic);
}


void supprimerJoueur(Joueur* j)
{
    char fichier[36];
    strcpy(fichier, "../data/joueurs");
    strcat(fichier, j->pseudo);
    strcat(fichier, ".sok");
    remove(fichier);
}
