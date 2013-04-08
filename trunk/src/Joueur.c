#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "Joueur.h"


void initialiserJoueur(Joueur* j, const char* pseudo)
{
    assert(strlen(pseudo) < 16);
    strcpy(j->pseudo, pseudo);
    j->avancement = 1;

    strcpy(j->fichier, "../data/joueurs/");
    strcat(j->fichier, j->pseudo);
    strcat(j->fichier, ".sok");

    /* Sauvegarde des données du joueur */
    FILE* fic = fopen(j->fichier, "wb");
    fwrite(j->pseudo, 16, 1, fic);
    fwrite(&(j->avancement), 4, 1, fic);
    fclose(fic);
}


void chargerJoueur(Joueur* j, const char* fichier)
{
    strcpy(j->fichier, fichier);
    FILE* fic = fopen(fichier, "rb");
    fread(j->pseudo, 16, 1, fic);
    fread(&j->avancement, 4, 1, fic);
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
    FILE* fic = fopen(j->fichier, "a+b");
    fseek(fic, 16, SEEK_SET);
    fwrite(&j->avancement, 4, 1, fic);
    fclose(fic);
}


void supprimerJoueur(Joueur* j)
{
    remove(j->fichier);
}
