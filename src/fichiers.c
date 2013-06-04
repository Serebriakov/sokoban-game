#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <dirent.h>

#include "fichiers.h"


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

    assert(niv <= nbNiveaux()); // Vérifie que le niveau existe
    n->num = niv; // Met à jour le numéro du niveau

    strcpy(fichier, "data/niveaux/");
    char niveau[3];
    sprintf(niveau, "%d", niv);
    strcat(fichier, niveau); // Le nom du fichier de niveau est de la forme "data/niveaux/xx.sok"
    strcat(fichier, ".sok");

    fic = fopen(fichier, "r");
    fscanf(fic, "%d %d ", &dimx, &dimy); // Récupère les dimensions du niveau qui sont écrites au début du fichier
    char ligneFichier[dimx*dimy+1]; // Contiendra les données du niveau
    fgets(ligneFichier, dimx*dimy+1, fic); // Les données du niveau sont stockées sur une seule ligne de taille dimx*dimy
    fclose(fic);

    libererNiveau(n); // Le niveau est une structure dynamique qui peut changer de taille. On commence par libérer l'espace alloué.
    initialiserNiveau(n, dimx, dimy); // Puis on réinitialise le niveau avec les nouvelles dimensions récupérées précédemment.


    // Recopie les données du niveau
    for (j = 0; j < obtenirDimYNiveau(n); j++)
    {
        for (i = 0; i < obtenirDimXNiveau(n); i++)
        {
            switch(ligneFichier[j*dimx+i])
            {
            case '0':
                modifierElementNiveau(n, i, j, 0);
                break;
            case '1':
                modifierElementNiveau(n, i, j, 1);
                break;
            case '2':
                modifierElementNiveau(n, i, j, 2);
                break;
            case '3':
                modifierElementNiveau(n, i, j, 3);
                break;
            case '4':
                modifierElementNiveau(n, i, j, 4);
                break;
            case '5':
                modifierElementNiveau(n, i, j, 5);
                break;
            case '6':
                modifierElementNiveau(n, i, j, 6);
                break;
            case '7':
                modifierElementNiveau(n, i, j, 7);
                break;
            case '8':
                modifierElementNiveau(n, i, j, 8);
                break;
            case '9':
                modifierElementNiveau(n, i, j, 9);
                break;
			default:
				break;
            }
        }
    }
}

void sauvegarderNiveau(const Niveau *n, const char *fichier)
{
    int i, j;

    FILE *fic = NULL;
    fic = fopen(fichier, "w+"); // Ouverture du fichier en mode écriture
    assert (fic != NULL);

    // Recopie les dimensions du niveau
    fprintf(fic, "%d ", obtenirDimXNiveau(n));
    fprintf(fic, "%d ", obtenirDimYNiveau(n));

    // Recopie les données du niveau
    for (j = 0; j < obtenirDimYNiveau(n); j++)
    {
        for (i = 0; i < obtenirDimXNiveau(n); i++)
        {
            fprintf(fic, "%d", obtenirElementNiveau(n, i, j));
        }
    }
    fclose(fic); // Fermeture du fichier
}


int nbNiveaux()
{
	int nb = 0;
	DIR *dir = NULL;
	struct dirent *entry = NULL;
	dir = opendir("data/niveaux");
    while ((entry = readdir(dir)))
    {
        if (strcmp(entry->d_name, ".") == 0) continue;
        if (strcmp(entry->d_name, "..") == 0) continue;
		nb++;
    } 
	return nb;
}


/*////////////////////////////////////////////////
// FONCTIONS DE GESTION DES FICHIERS DE JOUEURS //
////////////////////////////////////////////////*/
int creerJoueur(Joueur *j, const char *pseudo)
{
	// Vérifie que le max de joueurs n'ait pas été atteint
	DIR *dir = NULL;
    struct dirent *entry;
	int i = 3; // 3 est le nombre maximum de joueurs
	dir =  opendir("data/joueurs");
    while ((entry = readdir(dir)))
    {
        if (strcmp(entry->d_name, ".") == 0) continue;
        if (strcmp(entry->d_name, "..") == 0) continue;
		char *pDot = strchr(entry->d_name, '.');
		*pDot = '\0';
		i--;
		if (strcmp(pseudo, entry->d_name) == 0) i++; // S'il y a déjà un joueur du même nom, on incrémente i afin qu'il ne soit jamais égal à 0 et qu'on puisse recréer le joueur par la suite
    } 
	if (i==0) return -1; // S'il y a déjà 3 joueurs de noms différents de celui du joueur que l'on veut créer, on ne le crée pas (le max est atteint)

	// S'il y a moins de 3 joueurs, ou que le joueur existe déjà, on crée un nouveau joueur
    assert(strlen(pseudo) < 16);
    char fichier[36]; // Contiendra le nom du fichier joueur
    FILE *fic = NULL;

    strcpy(j->pseudo, pseudo);
    modifierAvancement(j, 1); // Le joueur débute au niveau 1

    strcpy(fichier, "data/joueurs/");
    strcat(fichier, j->pseudo); // Le fichier joueur est de la forme "data/joueurs/pseudo.sok"
    strcat(fichier, ".sok");

    fic = fopen(fichier, "w"); // Ouverture du fichier joueur en mode écriture
    fprintf(fic, "%d ", obtenirAvancement(j)); // Ecriture de l'avancement du joueur

	// Ecriture des scores (initialisés à 0)
	for (i=0; i<20; i++)
	{
		fprintf(fic, "%d ", 0);
		modifierScore(j, i, 0);
	}
	
    fclose(fic);
	return 0;
}


void chargerJoueur(Joueur *j, const char *pseudo)
{
    char fichier[36]; // Contiendra le nom du fichier joueur
    FILE *fic = NULL;

    strcpy(fichier, "data/joueurs/");
    strcat(fichier, pseudo); // Le fichier joueur est de la forme "data/joueurs/pseudo.sok"
    strcat(fichier, ".sok");

    fic = fopen(fichier, "r"); // Ouverture du fichier joueur en mode lecture
	int niveau;
    fscanf(fic, "%d ", &niveau); // Lecture de l'avancement du joueur
	modifierAvancement(j, niveau);

	// Lecture des scores
	int i;
	int scores[20];
	for (i=0; i<20; i++)
	{
		fscanf(fic, "%d ", &(scores[i]));
		modifierScore(j, i, scores[i]);
	}

    fclose(fic);

	strcpy(j->pseudo, pseudo);
}


void sauvegarderJoueur(const Joueur *j)
{
    char fichier[36]; // Contiendra le nom du fichier joueur
    FILE *fic = NULL;

    strcpy(fichier, "data/joueurs/");
    strcat(fichier, j->pseudo); // Le fichier joueur est de la forme "data/joueurs/pseudo.sok"
    strcat(fichier, ".sok");

    fic = fopen(fichier, "r+"); // Ouverture du fichier en mode read/update

	// Mise à jour de l'avancement
	int niveau = obtenirAvancement(j);
    fprintf(fic, "%d ", niveau);

	// Récupération des meilleurs scores
	int i;
	int tab_scores[20];
	for (i=0; i<20; i++) fscanf(fic, "%d ", &(tab_scores[i]));

	// Mise à jour des meilleurs scores (minimums des nombres de mouvements)
	rewind(fic);
    fprintf(fic, "%d ", niveau);
	for (i=0; i<20; i++)
	{
		if (tab_scores[i] == 0 || j->scores[i] < tab_scores[i]) fprintf(fic, "%d ", j->scores[i]);
		else fprintf(fic, "%d ", tab_scores[i]);
	}

	// Fermeture du fichier
    fclose(fic);
}


void supprimerJoueur(const char *pseudo)
{
    char fichier[36]; // Contiendra le nom du fichier joueur

    strcpy(fichier, "data/joueurs/");
    strcat(fichier, pseudo); // Le fichier joueur est de la forme "data/joueurs/pseudo.sok"
    strcat(fichier, ".sok");
    remove(fichier); // Suppression du fichier (sans confirmation)
}

