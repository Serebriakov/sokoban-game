#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <dirent.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "afficheSDL.h"


/*//////////////////////////////
////////// BOUCLE JEU //////////
//////////////////////////////*/


// Première partie de afficherJeu
void afficherNiveau(const Niveau *n, SDL_Surface **sprites, int direction_joueur, SDL_Surface *ecran)
{
	// Détermination du monde
	int monde;
	int num_niveau = obtenirNumNiveau(n);
	if (1 <= num_niveau && num_niveau <= 5) monde = 1;
	if (6 <= num_niveau && num_niveau <= 10) monde = 2;
	if (11 <= num_niveau && num_niveau <= 15) monde = 3;
	if (16 <= num_niveau && num_niveau <= 20) monde = 4;
	if (num_niveau >= 21) monde = 5;

	// Affichage des surfaces
	SDL_Rect position;
	position.x = 0;
	position.y = 0;
	// 1. Affichage du fond
	SDL_BlitSurface(sprites[0], NULL, ecran, &position);
	// 2. Positionnement du premier élément en fonction du monde
	switch (monde)
	{
		case 1:
			position.x = (600- n->dimx*25)/2;
			position.y = 140;
			break;
		case 2:
			position.x = 50;
			position.y = (600 - n->dimy*25)/2;
			break;
		case 3:
			position.x = 300;
			position.y = (600 - n->dimy*25)/2;
			break;
		case 4:
			position.x = 50;
			position.y = (600 - n->dimy*25)/2;
			break;
		case 5:
			position.x = 150;
			position.y = 150;
			break;
	}
	// 3. Boucle d'affichage des éléments du niveau (ligne par ligne)
    int i, j;
    for (j = 0; j < n->dimy; j++)
    {
        for (i = 0; i < n->dimx; i++)
        {
            switch(obtenirElementNiveau(n, i, j))
			{
				case JOUEUR:
					switch(direction_joueur)
					{
						case HAUT:
							SDL_BlitSurface(sprites[1], NULL, ecran, &position);
							break;
						case BAS:
							SDL_BlitSurface(sprites[2], NULL, ecran, &position);
							break;
						case GAUCHE:
							SDL_BlitSurface(sprites[3], NULL, ecran, &position);
							break;
						case DROITE:
							SDL_BlitSurface(sprites[4], NULL, ecran, &position);
							break;
					}
					break;
				case JOUEUR_CIBLE:
					switch(direction_joueur)
					{
						case HAUT:
							SDL_BlitSurface(sprites[1], NULL, ecran, &position);
							break;
						case BAS:
							SDL_BlitSurface(sprites[2], NULL, ecran, &position);
							break;
						case GAUCHE:
							SDL_BlitSurface(sprites[3], NULL, ecran, &position);
							break;
						case DROITE:
							SDL_BlitSurface(sprites[4], NULL, ecran, &position);
							break;
					}
					break;
				case CAISSE:
					SDL_BlitSurface(sprites[5], NULL, ecran, &position);
					break;
				case CIBLE:
					SDL_BlitSurface(sprites[6], NULL, ecran, &position);
					break;
				case CAISSE_OK:
					SDL_BlitSurface(sprites[7], NULL, ecran, &position);
					break;
				case MUR:
					SDL_BlitSurface(sprites[8], NULL, ecran, &position);
					break;
				case ELEM_DECOR1:
					SDL_BlitSurface(sprites[9], NULL, ecran, &position);
					break;
				case ELEM_DECOR2:
					SDL_BlitSurface(sprites[10], NULL, ecran, &position);
					break;
				default:
					break;
			}
			position.x += 25;
        }
	// Positionnement du premier élément de la ligne suivante
	switch (monde)
	{
		case 1:
			position.x = (600- n->dimx*25)/2;
			break;
		case 2:
			position.x = 50;
			break;
		case 3:
			position.x = 300;
			break;
		case 4:
			position.x = 50;
			break;
		case 5:
			position.x = 150;
			break;
	}
	position.y += 25;
    }
}


// Deuxième partie de afficherJeu
void afficherAvancementJoueur(Joueur *j, SDL_Surface *ecran)
{
	int num = obtenirAvancement(j);
	char niv[2];
	sprintf(niv, "%d", num);

	// Initialisation de la surface
	SDL_Surface *texte = NULL;

	SDL_Color couleur = {255, 255, 255};
	SDL_Rect position;
	position.x = 170;
	position.y = 21;

	TTF_Font *police = NULL;
	police = TTF_OpenFont("data/polices/heygorgeous.ttf", 18);
	texte = TTF_RenderText_Blended(police, niv, couleur);

	SDL_BlitSurface(texte, NULL, ecran, &position);

	// Libération de la surface
	SDL_FreeSurface(texte);

	TTF_CloseFont(police);
}


// Troisième et dernière partie de afficherJeu
void afficherNbMvmts(int nb_mvmts, SDL_Surface *ecran)
{
	char nb[4];
	sprintf(nb, "%d", nb_mvmts);

	// Initialisation de la surface
	SDL_Surface *texte = NULL;

	SDL_Color couleur = {255, 255, 255}; // blanc
	SDL_Rect position;
	position.x = 530;
	position.y = 21;

	TTF_Font *police = NULL;
	police = TTF_OpenFont("data/polices/heygorgeous.ttf", 18);
	texte = TTF_RenderText_Blended(police, nb, couleur);

	SDL_BlitSurface(texte, NULL, ecran, &position);

	// Libération de la surface
	SDL_FreeSurface(texte);

	// Libération de la police
	TTF_CloseFont(police);
}


void afficherJeu(Jeu *j, SDL_Surface **sprites, int direction_joueur, int nb_mvmts, SDL_Surface *ecran)
{
    afficherNiveau(&(j->niveau), sprites, direction_joueur, ecran);
    afficherAvancementJoueur(&(j->joueur), ecran);
	afficherNbMvmts(nb_mvmts, ecran);
	SDL_Flip(ecran);
}


void boucleJeu(Jeu *j, SDL_Surface *ecran)
{
	int direction_joueur;
	int nb_mvmts;

	// Détermination du monde
	int monde;
	int num_niveau = obtenirNumNiveau(&(j->niveau));
	if (1 <= num_niveau && num_niveau <= 5) monde = 1;
	if (6 <= num_niveau && num_niveau <= 10) monde = 2;
	if (11 <= num_niveau && num_niveau <= 15) monde = 3;
	if (16 <= num_niveau && num_niveau <= 20) monde = 4;
	if (num_niveau >= 21) monde = 5; // Niveaux de l'éditeur

	// Initialisation des surfaces (sprites)
	SDL_Surface *sprites[11];

	// Chargement des sprites en fonction du monde
	switch (monde)
	{
		case 1:
			sprites[0] = IMG_Load("data/images/monde1/bg.jpg");
			sprites[1] = IMG_Load("data/images/monde1/joueur_haut.png");
			sprites[2] = IMG_Load("data/images/monde1/joueur_bas.png");
			sprites[3] = IMG_Load("data/images/monde1/joueur_gauche.png");
			sprites[4] = IMG_Load("data/images/monde1/joueur_droite.png");
			sprites[5] = IMG_Load("data/images/monde1/caisse.png");
			sprites[6] = IMG_Load("data/images/monde1/cible.png");
			sprites[7] = IMG_Load("data/images/monde1/caisse_ok.png");
			sprites[8] = IMG_Load("data/images/monde1/mur.gif");
			sprites[9] = IMG_Load("data/images/monde1/decor1.gif");
			sprites[10] = IMG_Load("data/images/monde1/decor2.gif");
			break;
		case 2:
			sprites[0] = IMG_Load("data/images/monde2/bg.jpg");
			sprites[1] = IMG_Load("data/images/monde2/joueur_haut.png");
			sprites[2] = IMG_Load("data/images/monde2/joueur_bas.png");
			sprites[3] = IMG_Load("data/images/monde2/joueur_gauche.png");
			sprites[4] = IMG_Load("data/images/monde2/joueur_droite.png");
			sprites[5] = IMG_Load("data/images/monde2/caisse.png");
			sprites[6] = IMG_Load("data/images/monde2/cible.png");
			sprites[7] = IMG_Load("data/images/monde2/caisse_ok.png");
			sprites[8] = IMG_Load("data/images/monde2/mur.png");
			sprites[9] = IMG_Load("data/images/monde2/decor1.png");
			sprites[10] = IMG_Load("data/images/monde2/decor2.png");
			break;
		case 3:
			sprites[0] = IMG_Load("data/images/monde3/bg.jpg");
			sprites[1] = IMG_Load("data/images/monde3/joueur_haut.png");
			sprites[2] = IMG_Load("data/images/monde3/joueur_bas.png");
			sprites[3] = IMG_Load("data/images/monde3/joueur_gauche.png");
			sprites[4] = IMG_Load("data/images/monde3/joueur_droite.png");
			sprites[5] = IMG_Load("data/images/monde3/caisse.png");
			sprites[6] = IMG_Load("data/images/monde3/cible.png");
			sprites[7] = IMG_Load("data/images/monde3/caisse_ok.png");
			sprites[8] = IMG_Load("data/images/monde3/mur.png");
			sprites[9] = IMG_Load("data/images/monde3/decor1.png");
			sprites[10] = IMG_Load("data/images/monde3/decor2.png");
			break;
		case 4:
			sprites[0] = IMG_Load("data/images/monde4/bg.jpg");
			sprites[1] = IMG_Load("data/images/monde4/joueur_haut.png");
			sprites[2] = IMG_Load("data/images/monde4/joueur_bas.png");
			sprites[3] = IMG_Load("data/images/monde4/joueur_gauche.png");
			sprites[4] = IMG_Load("data/images/monde4/joueur_droite.png");
			sprites[5] = IMG_Load("data/images/monde4/caisse.png");
			sprites[6] = IMG_Load("data/images/monde4/cible.png");
			sprites[7] = IMG_Load("data/images/monde4/caisse_ok.png");
			sprites[8] = IMG_Load("data/images/monde4/mur.png");
			sprites[9] = IMG_Load("data/images/monde4/decor1.png");
			sprites[10] = IMG_Load("data/images/monde4/decor2.png");
			break;
		case 5:
			sprites[0] = IMG_Load("data/images/editeur/bg.jpg");
			sprites[1] = IMG_Load("data/images/editeur/joueur_haut.png");
			sprites[2] = IMG_Load("data/images/editeur/joueur_bas.png");
			sprites[3] = IMG_Load("data/images/editeur/joueur_gauche.png");
			sprites[4] = IMG_Load("data/images/editeur/joueur_droite.png");
			sprites[5] = IMG_Load("data/images/editeur/caisse.png");
			sprites[6] = IMG_Load("data/images/editeur/cible.png");
			sprites[7] = IMG_Load("data/images/editeur/caisse_ok.png");
			sprites[8] = IMG_Load("data/images/editeur/mur.png");
			sprites[9] = IMG_Load("data/images/editeur/decor1.png");
			sprites[10] = IMG_Load("data/images/editeur/decor2.png");
			break;
		default:
			break;
	}		

	// Initialisation de la musique
	Mix_Music *musique = NULL;

	// Chargement de la musique en fonction du monde
	switch (monde)
	{
		case 1:
			musique = Mix_LoadMUS("data/son/monde1/musique.mp3");
			break;
		case 2:
			musique = Mix_LoadMUS("data/son/monde2/musique.mp3");
			break;
		case 3:
			musique = Mix_LoadMUS("data/son/monde3/musique.mp3");
			break;
		case 4:
			musique = Mix_LoadMUS("data/son/monde4/musique.mp3");
			break;
		case 5:
			musique = Mix_LoadMUS("data/son/editeur/musique.mp3");
			break;
	}

	// Lecture en boucle de la musique
	Mix_PlayMusic(musique, -1);

	// Initialisation des bruitages
	Mix_Chunk *mur = NULL;
	Mix_Chunk *fin_niveau = NULL;

	// Chargement des bruitages en fonction du monde
	switch (monde)
	{
		case 1:
			mur = Mix_LoadWAV("data/son/monde1/mur.wav");
			fin_niveau = Mix_LoadWAV("data/son/monde1/fin_niveau.wav");
			break;
		case 2:
			mur = Mix_LoadWAV("data/son/monde2/mur.wav");
			fin_niveau = Mix_LoadWAV("data/son/monde2/fin_niveau.wav");
			break;
		case 3:
			mur = Mix_LoadWAV("data/son/monde3/mur.wav");
			fin_niveau = Mix_LoadWAV("data/son/monde3/fin_niveau.wav");
			break;
		case 4:
			mur = Mix_LoadWAV("data/son/monde4/mur.wav");
			fin_niveau = Mix_LoadWAV("data/son/monde4/fin_niveau.wav");
			break;
		case 5:
			mur = Mix_LoadWAV("data/son/editeur/mur.wav");
			fin_niveau = Mix_LoadWAV("data/son/editeur/fin_niveau.wav");
			break;
	}

	// Boucle événementielle
	SDL_Event event;
    while (!finJeu(j))
    {
		direction_joueur = GAUCHE; // Au début du niveau, le joueur est dirigé vers la gauche
		nb_mvmts = 0;

		afficherJeu(j, sprites, direction_joueur, nb_mvmts, ecran);

        do
        {
           	SDL_WaitEvent(&event);
			switch (event.type)
			{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_UP:
							if (!jeuClavier(j, 'h')) Mix_PlayChannel(-1, mur, 0);
							direction_joueur = HAUT;
							nb_mvmts++;
							break;
						case SDLK_DOWN:
							if (!jeuClavier(j, 'b')) Mix_PlayChannel(-1, mur, 0);
							direction_joueur = BAS;
							nb_mvmts++;
							break;
						case SDLK_LEFT:
							if (!jeuClavier(j, 'g')) Mix_PlayChannel(-1, mur, 0);
							direction_joueur = GAUCHE;
							nb_mvmts++;
							break;
						case SDLK_RIGHT:
							if (!jeuClavier(j, 'd')) Mix_PlayChannel(-1, mur, 0);
							direction_joueur = DROITE;
							nb_mvmts++;
							break;
						case SDLK_r: // Recommencer
							chargerNiveau(&(j->niveau), (j->niveau).num); // On charge le même niveau
							direction_joueur = GAUCHE;
							nb_mvmts = 0;							
							break;
						case SDLK_ESCAPE:
						case SDLK_q: // Retour
							quitterJeu(j); // Libère le jeu et sauvegarde

							// Libération des surfaces (sprites)
							int k;
							for (k=0; k<11; k++) SDL_FreeSurface(sprites[k]);
	
							// Libération de la musique (arrête la musique)
							Mix_FreeMusic(musique);

							// Libération des bruitages
							Mix_FreeChunk(mur);
							Mix_FreeChunk(fin_niveau);
							return; // Retour au menu
						default:
							break;
					}
					afficherJeu(j, sprites, direction_joueur, nb_mvmts, ecran);
					break;	
			}
        }
        while (!finNiveau(&(j->niveau)));

		// Enregistrement du score
		modifierScore(&(j->joueur), obtenirAvancement(&(j->joueur))-1, nb_mvmts);	

        if (obtenirNumNiveau(&(j->niveau)) < nbNiveaux()) niveauSuivant(j); // On passe au niveau suivant
		else modifierNumNiveau(&(j->niveau), obtenirNumNiveau(&(j->niveau))+1); // Indique la fin du jeu

		// Lecture du bruitage de fin de niveau
		Mix_PlayChannel(-1, fin_niveau, 0);
		SDL_Delay(1000);

		// Si on entre dans un nouveau monde, on change la musique
		num_niveau = obtenirNumNiveau(&(j->niveau));
		if (num_niveau == 6)
		{
			musique = Mix_LoadMUS("data/son/monde2/musique.mp3");
			Mix_PlayMusic(musique, -1);
		}
		if (num_niveau == 11)
		{
			musique = Mix_LoadMUS("data/son/monde3/musique.mp3");
			Mix_PlayMusic(musique, -1);
		}
		if (num_niveau == 16)
		{
			musique = Mix_LoadMUS("data/son/monde4/musique.mp3");
			Mix_PlayMusic(musique, -1);
		}
		if (num_niveau == 21)
		{
			musique = Mix_LoadMUS("data/son/editeur/musique.mp3");
			Mix_PlayMusic(musique, -1);
		}

		// Et les bruitages
		if (num_niveau == 6)
		{	
			mur = Mix_LoadWAV("data/son/monde2/mur.wav");
			fin_niveau = Mix_LoadWAV("data/son/monde2/fin_niveau.wav");
		}
		if (num_niveau == 11)
		{
			mur = Mix_LoadWAV("data/son/monde3/mur.wav");
			fin_niveau = Mix_LoadWAV("data/son/monde3/fin_niveau.wav");
		}
		if (num_niveau == 16)
		{
			mur = Mix_LoadWAV("data/son/monde4/mur.wav");
			fin_niveau = Mix_LoadWAV("data/son/monde4/fin_niveau.wav");
		}
		if (num_niveau == 21)
		{
			mur = Mix_LoadWAV("data/son/editeur/mur.wav");
			fin_niveau = Mix_LoadWAV("data/son/editeur/fin_niveau.wav");
		}
		// Et les sprites
		if (num_niveau == 6)
		{	
			sprites[0] = IMG_Load("data/images/monde2/bg.jpg");
			sprites[1] = IMG_Load("data/images/monde2/joueur_haut.png");
			sprites[2] = IMG_Load("data/images/monde2/joueur_bas.png");
			sprites[3] = IMG_Load("data/images/monde2/joueur_gauche.png");
			sprites[4] = IMG_Load("data/images/monde2/joueur_droite.png");
			sprites[5] = IMG_Load("data/images/monde2/caisse.png");
			sprites[6] = IMG_Load("data/images/monde2/cible.png");
			sprites[7] = IMG_Load("data/images/monde2/caisse_ok.png");
			sprites[8] = IMG_Load("data/images/monde2/mur.png");
			sprites[9] = IMG_Load("data/images/monde2/decor1.png");
			sprites[10] = IMG_Load("data/images/monde2/decor2.png");
			monde = 2;
		}
		if (j->niveau.num == 11)
		{
			sprites[0] = IMG_Load("data/images/monde3/bg.jpg");
			sprites[1] = IMG_Load("data/images/monde3/joueur_haut.png");
			sprites[2] = IMG_Load("data/images/monde3/joueur_bas.png");
			sprites[3] = IMG_Load("data/images/monde3/joueur_gauche.png");
			sprites[4] = IMG_Load("data/images/monde3/joueur_droite.png");
			sprites[5] = IMG_Load("data/images/monde3/caisse.png");
			sprites[6] = IMG_Load("data/images/monde3/cible.png");
			sprites[7] = IMG_Load("data/images/monde3/caisse_ok.png");
			sprites[8] = IMG_Load("data/images/monde3/mur.png");
			sprites[9] = IMG_Load("data/images/monde3/decor1.png");
			sprites[10] = IMG_Load("data/images/monde3/decor2.png");
			monde = 3;
		}
		if (j->niveau.num == 16)
		{
			sprites[0] = IMG_Load("data/images/monde4/bg.jpg");
			sprites[1] = IMG_Load("data/images/monde4/joueur_haut.png");
			sprites[2] = IMG_Load("data/images/monde4/joueur_bas.png");
			sprites[3] = IMG_Load("data/images/monde4/joueur_gauche.png");
			sprites[4] = IMG_Load("data/images/monde4/joueur_droite.png");
			sprites[5] = IMG_Load("data/images/monde4/caisse.png");
			sprites[6] = IMG_Load("data/images/monde4/cible.png");
			sprites[7] = IMG_Load("data/images/monde4/caisse_ok.png");
			sprites[8] = IMG_Load("data/images/monde4/mur.png");
			sprites[9] = IMG_Load("data/images/monde4/decor1.png");
			sprites[10] = IMG_Load("data/images/monde4/decor2.png");
			monde = 4;
		}
		if (num_niveau == 21)
		{
			sprites[0] = IMG_Load("data/images/editeur/bg.jpg");
			sprites[1] = IMG_Load("data/images/editeur/joueur_haut.png");
			sprites[2] = IMG_Load("data/images/editeur/joueur_bas.png");
			sprites[3] = IMG_Load("data/images/editeur/joueur_gauche.png");
			sprites[4] = IMG_Load("data/images/editeur/joueur_droite.png");
			sprites[5] = IMG_Load("data/images/editeur/caisse.png");
			sprites[6] = IMG_Load("data/images/editeur/cible.png");
			sprites[7] = IMG_Load("data/images/editeur/caisse_ok.png");
			sprites[8] = IMG_Load("data/images/editeur/mur.png");
			sprites[9] = IMG_Load("data/images/editeur/decor1.png");
			sprites[10] = IMG_Load("data/images/editeur/decor2.png");
			monde = 5;
		}
    }

	// Libération des surfaces (sprites)
	int k;
	for (k=0; k<11; k++) SDL_FreeSurface(sprites[k]);
	
	// Libération de la musique (arrête la musique)
	Mix_FreeMusic(musique);

	// Libération des bruitages
	Mix_FreeChunk(mur);
	Mix_FreeChunk(fin_niveau);

	quitterJeu(j); // Libère le jeu et sauvegarde
    return; // Retour au menu
}



/*///////////////////////////////
////////// BOUCLE MENU //////////
///////////////////////////////*/


// Pour "Charger une partie" et "Ecraser une partie"
void afficherJoueurs(SDL_Surface *ecran)
{
	// Initialisation de la surface
	SDL_Surface *texte = NULL; 
	
	SDL_Rect position;
	position.y = 183; // Positionnement vertical du premier joueur
	SDL_Color couleur = {0, 0, 0};

	TTF_Font *police = NULL;
	police = TTF_OpenFont("data/polices/heygorgeous.ttf", 18);

	// Parcours du répertoire "joueurs"
    DIR *dir = NULL;
	dir = opendir("data/joueurs");
    struct dirent *entry = NULL;
	int i = 3; // 3 est le nombre maximum de joueurs

    while ((entry = readdir(dir)))
    {
        if (strcmp(entry->d_name, ".") == 0) continue;
        if (strcmp(entry->d_name, "..") == 0) continue;

		// Suppression de l'extension de fichier (.sok)
        char *pDot = strchr(entry->d_name, '.');
        *pDot = '\0';

		// Affichage du nom du joueur
		texte = TTF_RenderText_Blended(police, entry->d_name, couleur);
		position.x = (600 - texte->w)/2;
		SDL_BlitSurface(texte, NULL, ecran, &position);
		position.y = position.y + 127; // Positionnement vertical du joueur suivant
		i--;
    }	
    closedir(dir);

	// i est maintenant égal au nombre de parties libres
	while (i>0)
	{
		texte = TTF_RenderText_Blended(police, "Partie libre", couleur);
		position.x = (600 - texte->w)/2;
		SDL_BlitSurface(texte, NULL, ecran, &position);		
		position.y = position.y + 127;
		i--;
	}

	TTF_CloseFont(police);

	// Mise à jour du buffer
	SDL_Flip(ecran);

	// Libération de la surface
	SDL_FreeSurface(texte);
}


int ecrasement(SDL_Surface *ecran)
{
	// Initialisation des surfaces
	SDL_Surface *ecrasement[3] = {NULL};

	// Chargement des surfaces
	ecrasement[0] = IMG_Load("data/images/partie/ecrasement_1.jpg"); // Joueur 1
	ecrasement[1] = IMG_Load("data/images/partie/ecrasement_2.jpg"); // Joueur 2
	ecrasement[2] = IMG_Load("data/images/partie/ecrasement_3.jpg"); // Joueur 3

	// Affichage de la première surface
	SDL_Event event;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;
	SDL_BlitSurface(ecrasement[0], NULL, ecran, &position);
	SDL_Flip(ecran);

	// Affichage des joueurs par-dessus
	afficherJoueurs(ecran);
	
	// Boucle événementielle
	int continuer = 1;
	int choix = 0;
	int j = 0;
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
						choix = ((choix - 1)%3 + 3)%3;
						SDL_BlitSurface(ecrasement[choix], NULL, ecran, &position);
						afficherJoueurs(ecran);
						SDL_Flip(ecran);
						break;
					case SDLK_DOWN:
						choix = (choix + 1)%3;
						SDL_BlitSurface(ecrasement[choix], NULL, ecran, &position);
						afficherJoueurs(ecran);
						SDL_Flip(ecran);
						break;
					case SDLK_RETURN:
						continuer = 0;
						break;
					case SDLK_ESCAPE:
					case SDLK_q:
						// Libération des surfaces
						while (j<3)
						{
							SDL_FreeSurface(ecrasement[j]);
							j++;
						}
						return 0; // L'utilisateur a finalement choisi de ne pas écraser de joueur
					default:
						break;
				}
				break;
			default:
				break;
		}
	}

	// Récupération du pseudo du joueur que l'on veut écraser
	char pseudo[16];
	DIR *dir = NULL;
	dir = opendir("data/joueurs");
    struct dirent *entry = NULL;
	int i = choix;
    while ((entry = readdir(dir)) && i>=0)
    {
        if (strcmp(entry->d_name, ".") == 0) continue;
        if (strcmp(entry->d_name, "..") == 0) continue;
   		char *pDot = strchr(entry->d_name, '.');
    	*pDot = '\0';
		strcpy(pseudo, entry->d_name);
		i--;
    }
	closedir(dir);

	// Ecrasement du joueur
	supprimerJoueur(pseudo);
	
	// Libération des surfaces
	while (j<3)
	{
		SDL_FreeSurface(ecrasement[j]);
		j++;
	}

	return 1; // L'écrasement a eu lieu
}
	

void nouvellePartie(SDL_Surface *ecran)
{
    Jeu j;
    char pseudo[16];

	// Initialisation des surfaces
	SDL_Surface *saisie_pseudo = NULL;
	SDL_Surface *affichage_pseudo = NULL;

	// Chargement de la surface saisie_pseudo
	saisie_pseudo = IMG_Load("data/images/partie/saisie_pseudo.jpg");

	// Affichage de la surface saisie_pseudo
	SDL_Rect position;
	position.x = 0;
	position.y = 0;
	SDL_BlitSurface(saisie_pseudo, NULL, ecran, &position);

	SDL_Color couleur = {0, 0, 0};
    
	TTF_Font *police = NULL;
	police = TTF_OpenFont("data/polices/heygorgeous.ttf", 18);
	affichage_pseudo = TTF_RenderText_Blended(police, "-", couleur);

	// Affichage de la saisie initiale "-"
	position.x = (600-affichage_pseudo->w)/2;
	position.y = 310;
	SDL_BlitSurface(affichage_pseudo, NULL, ecran, &position);
	SDL_Flip(ecran);

	// Boucle événementielle
	SDL_Event event;
	int continuer = 1;
	int nb_lettres = 0; // Le pseudo devra contenir 15 caractères maximum
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_a:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'A';
							nb_lettres++;
						}
						break;
					case SDLK_b:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'B';
							nb_lettres++;
						}
						break;
					case SDLK_c:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'C';
							nb_lettres++;
						}
						break;
					case SDLK_d:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'D';
							nb_lettres++;
						}
						break;
					case SDLK_e:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'E';
							nb_lettres++;
						}
						break;
					case SDLK_f:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'F';
							nb_lettres++;
						}
						break;
					case SDLK_g:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'G';
							nb_lettres++;
						}
						break;
					case SDLK_h:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'H';
							nb_lettres++;
						}
						break;
					case SDLK_i:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'I';
							nb_lettres++;
						}
						break;
					case SDLK_j:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'J';
							nb_lettres++;
						}
						break;
					case SDLK_k:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'K';
							nb_lettres++;
						}
						break;
					case SDLK_l:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'L';
							nb_lettres++;
						}
						break;
					case SDLK_m:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'M';
							nb_lettres++;
						}
						break;
					case SDLK_n:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'N';
							nb_lettres++;
						}
						break;
					case SDLK_o:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'O';
							nb_lettres++;
						}
						break;
					case SDLK_p:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'P';
							nb_lettres++;
						}
						break;
					case SDLK_q:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'Q';
							nb_lettres++;
						}
						break;
					case SDLK_r:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'R';
							nb_lettres++;
						}
						break;
					case SDLK_s:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'S';
							nb_lettres++;
						}
						break;
					case SDLK_t:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'T';
							nb_lettres++;
						}
						break;
					case SDLK_u:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'U';
							nb_lettres++;
						}
						break;
					case SDLK_v:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'V';
							nb_lettres++;
						}
						break;
					case SDLK_w:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'W';
							nb_lettres++;
						}
						break;
					case SDLK_x:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'X';
							nb_lettres++;
						}
						break;
					case SDLK_y:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'Y';
							nb_lettres++;
						}
						break;
					case SDLK_z:
						if (nb_lettres < 15)
						{
							pseudo[nb_lettres] = 'Z';
							nb_lettres++;
						}
						break;
					case SDLK_BACKSPACE:
						if (nb_lettres > 0)
						{
							nb_lettres--;
						}
						break;
					case SDLK_ESCAPE:
						TTF_CloseFont(police);
	
						// Libération des surfaces
						SDL_FreeSurface(saisie_pseudo);
						SDL_FreeSurface(affichage_pseudo);
						return; // Retour au menu
					case SDLK_RETURN:
						if (nb_lettres != 0)
						{
							continuer = 0;
						}
						break;
					default:
						break;
				}
                // Affichage pseudo //
                pseudo[nb_lettres] = '\0';
                position.x = 0;
                position.y = 0;
                SDL_BlitSurface(saisie_pseudo, NULL, ecran, &position);
				if (nb_lettres != 0){
		        	affichage_pseudo = TTF_RenderText_Blended(police, pseudo, couleur);
		        	position.x = (600-affichage_pseudo->w)/2; // pour centrer horizontalement le texte
		        	position.y = 310;
		        	SDL_BlitSurface(affichage_pseudo, NULL, ecran, &position);
		        	SDL_Flip(ecran);
				}
				else {
		        	affichage_pseudo = TTF_RenderText_Blended(police, "-", couleur);
		        	position.x = (600-affichage_pseudo->w)/2; // pour centrer horizontalement le texte
		        	position.y = 310;
		        	SDL_BlitSurface(affichage_pseudo, NULL, ecran, &position);
		        	SDL_Flip(ecran);
				}
				break;
            default:
                break;
		}
	}

	TTF_CloseFont(police);
	
	// Libération des surfaces
	SDL_FreeSurface(saisie_pseudo);
	SDL_FreeSurface(affichage_pseudo);

	initialiserJeu(&j, pseudo);
	int ecrasement_ok = 1;
	if (creerJoueur(&(j.joueur), pseudo) == -1) ecrasement_ok = ecrasement(ecran);	// Il y a déjà trois joueurs, on demande à l'utilisateur quel joueur il souhaite écraser
	if (ecrasement_ok){
		creerJoueur(&(j.joueur), pseudo);
		boucleJeu(&j, ecran);
	} // Il y a moins de 3 joueurs (ecrasement_ok a été initialisé à 1) ou bien l'utilisateur a écrasé un joueur, on lance le jeu
	else return;
}


void chargerPartie(SDL_Surface *ecran)
{
    Jeu j;
    
	// Initialisation des surfaces
	SDL_Surface *choix_joueur[3] = {NULL};

	// Chargement des surfaces
	choix_joueur[0] = IMG_Load("data/images/partie/choix_joueur_1.jpg");
	choix_joueur[1] = IMG_Load("data/images/partie/choix_joueur_2.jpg");
	choix_joueur[2] = IMG_Load("data/images/partie/choix_joueur_3.jpg");

	// Affichage de la première surface
	SDL_Event event;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;
	SDL_BlitSurface(choix_joueur[0], NULL, ecran, &position);
	SDL_Flip(ecran);

	// Affichage des joueurs
	afficherJoueurs(ecran);

	// Boucle événementielle
	int continuer = 1;
	int choix = 0;
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
						choix = ((choix - 1)%3 + 3)%3;
						SDL_BlitSurface(choix_joueur[choix], NULL, ecran, &position);
						afficherJoueurs(ecran);
						SDL_Flip(ecran);
						break;
					case SDLK_DOWN:
						choix = (choix + 1)%3;
						SDL_BlitSurface(choix_joueur[choix], NULL, ecran, &position);
						afficherJoueurs(ecran);
						SDL_Flip(ecran);
						break;
					case SDLK_RETURN:
						continuer = 0;
						break;
					case SDLK_ESCAPE:
					case SDLK_q:
						// Libération des surfaces
						SDL_FreeSurface(choix_joueur[0]);
						SDL_FreeSurface(choix_joueur[1]);
						SDL_FreeSurface(choix_joueur[2]);
						return; // Retour au menu
					default:
						break;
				}
				break;
			default:
				break;
		}
	}

	// Récupération du pseudo choisi
	char pseudo[16];
	DIR *dir = NULL;
    struct dirent *entry = NULL;
	int i = choix;
	dir = opendir("data/joueurs");
    while ((entry = readdir(dir)) && i>=0)
    {
        if (strcmp(entry->d_name, ".") == 0) continue;
        if (strcmp(entry->d_name, "..") == 0) continue;
   		char *pDot = strchr(entry->d_name, '.');
    	*pDot = '\0';
		strcpy(pseudo, entry->d_name);
		i--;
    }
	closedir(dir);

	// Libération des surfaces
	SDL_FreeSurface(choix_joueur[0]);
	SDL_FreeSurface(choix_joueur[1]);
	SDL_FreeSurface(choix_joueur[2]);

    if (i!=-1) // Le joueur a choisi une partie libre
	{
		nouvellePartie(ecran);
	}
	else // Le joueur a choisi une partie existante
	{
		chargerJeu(&j, pseudo);
    	boucleJeu(&j, ecran);
	}
}


void editerNiveau(SDL_Surface *ecran)
{
	// Initialisation des surfaces
	SDL_Surface *editeur = NULL;
	SDL_Surface *joueur = NULL;
	SDL_Surface *vide = NULL;
	SDL_Surface *pomme = NULL;
	SDL_Surface *cible = NULL;
	SDL_Surface *mur = NULL;
	SDL_Surface *fleur = NULL;
	SDL_Surface *ogm = NULL;
	
	// Chargement des surfaces
	editeur = IMG_Load("data/images/editeur/editeur.jpg");
	joueur = IMG_Load("data/images/editeur/joueur_gauche.png");
	vide = IMG_Load("data/images/editeur/vide.png");
	pomme = IMG_Load("data/images/editeur/caisse.png");
	cible = IMG_Load("data/images/editeur/cible.png");
	mur = IMG_Load("data/images/editeur/mur.png");
	fleur = IMG_Load("data/images/editeur/decor1.png");
	ogm = IMG_Load("data/images/editeur/decor2.png");

	// Affichage de l'éditeur (niveau vide)
	SDL_Rect position;
	position.x = 0;
	position.y = 0;
	SDL_BlitSurface(editeur, NULL, ecran, &position);
	SDL_Flip(ecran);

	// Initialisation du niveau
	Niveau n;
	initialiserNiveau(&n, 12, 12);

	// Affichage de la case à modifier (tout en haut à gauche du niveau)
	SDL_Rect cm;
	cm.x = 22;
	cm.y = 88;
	cm.w = 5;
	cm.h = 5;
	SDL_FillRect(ecran, &cm, SDL_MapRGB(ecran->format, 0, 0, 0));
	SDL_Flip(ecran); // Le coin en haut à gauche de la case est rempli

	// Initialisation de la musique
	Mix_Music *musique = NULL;
	musique = Mix_LoadMUS("data/son/editeur/musique.mp3");
	
	// Lecture de la musique en boucle
	Mix_PlayMusic(musique, -1);

	// Coordonnées des éléments du niveau
	int x = 0;
	int y = 0;
	int i, j;

	// Pour les vérifications avant la sauvegarde
	Position pos_joueur;
	int nb_caisses = 0;
	int nb_cibles = 0;

	// Boucle événementielle
	int continuer = 1;
	SDL_Event event;
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_j: // Joueur
							if (obtenirElementNiveau(&n, x, y) == CAISSE) nb_caisses--;
							if (obtenirElementNiveau(&n, x, y) == CIBLE) nb_cibles--; 
							// S'il y a déjà un élément joueur, on le remplace par le vide
							pos_joueur = obtenirPositionJoueur(&n);
							if (pos_joueur.x != -1){
								modifierElementNiveau(&n, pos_joueur.x, pos_joueur.y, VIDE);
							}
							// Dans tous les cas on place le joueur aux coordonnées (x,y)
							modifierElementNiveau(&n, x, y, JOUEUR);
						break;
					case SDLK_v: // Vide
						if (obtenirElementNiveau(&n, x, y) == CAISSE) nb_caisses--;
						if (obtenirElementNiveau(&n, x, y) == CIBLE) nb_cibles--;
						modifierElementNiveau(&n, x, y, VIDE);
						break;
					case SDLK_p: // Pomme
						if (obtenirElementNiveau(&n, x, y) == CAISSE) nb_caisses--;
						if (obtenirElementNiveau(&n, x, y) == CIBLE) nb_cibles--;
						modifierElementNiveau(&n, x, y, CAISSE);
						nb_caisses++;
						break;
					case SDLK_c: // Cible
						if (obtenirElementNiveau(&n, x, y) == CAISSE) nb_caisses--;
						if (obtenirElementNiveau(&n, x, y) == CIBLE) nb_cibles--;
						modifierElementNiveau(&n, x, y, CIBLE);
						nb_cibles++;
						break;
					case SDLK_m: // Mur
						if (obtenirElementNiveau(&n, x, y) == CAISSE) nb_caisses--;
						if (obtenirElementNiveau(&n, x, y) == CIBLE) nb_cibles--;
						modifierElementNiveau(&n, x, y, MUR);
						break;					
					case SDLK_f: // Fleur
						if (obtenirElementNiveau(&n, x, y) == CAISSE) nb_caisses--;
						if (obtenirElementNiveau(&n, x, y) == CIBLE) nb_cibles--;
						modifierElementNiveau(&n, x, y, ELEM_DECOR1);
						break;			
					case SDLK_o: // OGM
						if (obtenirElementNiveau(&n, x, y) == CAISSE) nb_caisses--;
						if (obtenirElementNiveau(&n, x, y) == CIBLE) nb_cibles--;
						modifierElementNiveau(&n, x, y, ELEM_DECOR2);
						break;
					
					// Déplacements dans le niveau
					case SDLK_LEFT:
						if (x > 0)
						{
							x--;
							cm.x -= 25;
						}
						break;
					case SDLK_RIGHT:
						if (x < 11)
						{
							x++;
							cm.x += 25;
						}
						break;
					case SDLK_UP:
						if (y > 0)
						{
							y--;
							cm.y -= 25;
						}
						break;
					case SDLK_DOWN:
						if (y < 11)
						{
							y++;
							cm.y += 25;
						}
						break;
					case SDLK_ESCAPE:
					case SDLK_q:
						// Libération du niveau
						libererNiveau(&n);

						// Libération des surfaces
						SDL_FreeSurface(editeur);
						SDL_FreeSurface(joueur);
						SDL_FreeSurface(vide);
						SDL_FreeSurface(pomme);
						SDL_FreeSurface(cible);
						SDL_FreeSurface(mur);
						SDL_FreeSurface(fleur);
						SDL_FreeSurface(ogm);
	
						// Libération de la musique (arrête la musique)
						Mix_FreeMusic(musique);

						// Retour au menu
						return;
					case SDLK_s: // Sauvegarde
						// On vérifie qu'il y ait un joueur
						pos_joueur = obtenirPositionJoueur(&n);
						if (pos_joueur.x == -1) break;

						// On vérifie qu'il y ait autant de cibles que de caisses, et au moins une cible...
						if (nb_cibles != nb_caisses || nb_cibles < 1) break;
						
						// Si tout est ok, on sort de la boucle pour sauvegarder le niveau
						continuer = 0;
						break;
					default:
						break;
				}

				// On affiche le niveau actuel
				position.x = 0;
				position.y = 0;
				SDL_BlitSurface(editeur, NULL, ecran, &position);
				position.x = 22;
				position.y = 88;
		 		for (j = 0; j < 12; j++)
		   		{
					for (i = 0; i < 12; i++)
					{
						switch(obtenirElementNiveau(&n, i, j))
						{
							case JOUEUR:
								SDL_BlitSurface(joueur, NULL, ecran, &position);
								break;
							case CAISSE:
								SDL_BlitSurface(pomme, NULL, ecran, &position);
								break;
							case CIBLE:
								SDL_BlitSurface(cible, NULL, ecran, &position);
								break;
							case MUR:
								SDL_BlitSurface(mur, NULL, ecran, &position);
								break;
							case ELEM_DECOR1:
								SDL_BlitSurface(fleur, NULL, ecran, &position);
								break;
							case ELEM_DECOR2:
								SDL_BlitSurface(ogm, NULL, ecran, &position);
								break;
							default:
								SDL_BlitSurface(vide, NULL, ecran, &position);
								break;
						}
					position.x += 25;
					}
				position.x = 22;
				position.y += 25;
				}
				SDL_Flip(ecran);
				// Puis la nouvelle case à modifier
				SDL_FillRect(ecran, &cm, SDL_MapRGB(ecran->format, 0, 0, 0));
				SDL_Flip(ecran);
			default:
				break;
		}
	}

	// Sauvegarde du niveau dans un fichier
	char fichier[20];
	char num[3];
	sprintf(num, "%d", nbNiveaux()+1);
	strcpy(fichier, "data/niveaux/");
	strcat(fichier, num);
	strcat(fichier, ".sok");
	sauvegarderNiveau(&n, fichier);
	
	// Libération du niveau
	libererNiveau(&n);

	// Libération des surfaces
	SDL_FreeSurface(editeur);
	SDL_FreeSurface(joueur);
	SDL_FreeSurface(vide);
	SDL_FreeSurface(pomme);
	SDL_FreeSurface(cible);
	SDL_FreeSurface(mur);
	SDL_FreeSurface(fleur);
	SDL_FreeSurface(ogm);
	
	// Libération de la musique (arrête la musique)
	Mix_FreeMusic(musique);

	// Retour au menu
	return;
}


void consulterScores(SDL_Surface *ecran)
{
	// Initialisation des surfaces
	SDL_Surface *scores[4] = {NULL};
	SDL_Surface *texte = NULL;

	// Chargement des surfaces
	scores[0] = IMG_Load("data/images/scores/scores_monde1.jpg");
	scores[1] = IMG_Load("data/images/scores/scores_monde2.jpg");
	scores[2] = IMG_Load("data/images/scores/scores_monde3.jpg");
	scores[3] = IMG_Load("data/images/scores/scores_monde4.jpg");
	
	// Affichage de la première surface
	SDL_Rect position;
	position.x = 0;
	position.y = 0;
	SDL_BlitSurface(scores[0], NULL, ecran, &position);
	SDL_Flip(ecran);

	// Initialisation de l'effet sonore
	Mix_Chunk *curseur = NULL;

	// Chargement de l'effet sonore
	curseur = Mix_LoadWAV("data/son/menu/curseur.wav");

	// Initialisation de la police
	TTF_Font *police = NULL;
	
	// Chargement de la police
	police = TTF_OpenFont("data/polices/heygorgeous.ttf", 18);
	

	// DETERMINATION DES MEILLEURS SCORES
	int tab_scores[20][2]; // 20 scores auxquels on associe un joueur (0, 1 ou 2)
	 // 1. Ouverture des fichiers de tous les joueurs
	FILE *fic[3]; // 3 joueurs max
	char nom_fichier[35];
	char pseudos_joueurs[3][16];
	DIR *dir = NULL;
	struct dirent *entry = NULL;
	dir = opendir("data/joueurs/");
	int i = 0;
    while ((entry = readdir(dir)) && i<3)
    {
        if (strcmp(entry->d_name, ".") == 0) continue;
        if (strcmp(entry->d_name, "..") == 0) continue;
		strcpy(nom_fichier, "data/joueurs/");
		strcat(nom_fichier, entry->d_name);
		fic[i] = fopen(nom_fichier, "r");

		char *pDot = strchr(entry->d_name, '.');
		*pDot = '\0';
		strcpy(pseudos_joueurs[i], entry->d_name);
	 
		i++;
	}
	 // 2. Remplissage du tableau des scores
	int j;
	int k;
	int score;
	int meilleur_score;
	int meilleur_joueur;
	for (k=0; k<i; k++) fscanf(fic[k], "%d ", &meilleur_score); // on positionne la tête de lecture au premier score
	for (j=0; j<20; j++)
	{
		meilleur_score = 9999;
		meilleur_joueur = -1;
		for (k=0; k<i; k++)
		{
			fscanf(fic[k], "%d ", &score);
			if (score != 0 && score < meilleur_score)
			{
				meilleur_score = score;
				meilleur_joueur = k;
			}
		}
		tab_scores[j][0] = meilleur_score;
		tab_scores[j][1] = meilleur_joueur;
	}

	 // 3. Fermeture des fichiers de tous les joueurs
	while (i > 0)
	{
		fclose(fic[i-1]);
		i--;
	}

	// Affichage des scores du monde choisi
	int choix = 0;
	SDL_Rect position_score;
	SDL_Rect position_joueur;
	position_score.x = 110;
	position_score.y = 105;
	position_score.w = 170;
	position_score.h = 80;
	position_joueur.x = 295;
	position_joueur.y = 105;
	position_joueur.w = 270;
	position_joueur.h = 80;
	SDL_Color couleur = {0, 0, 0};
	char score_affiche[4];
	char joueur_affiche[16];
	
	for (i=0; i<5; i++)
	{
		if (tab_scores[choix*5+i][0] != 9999)
		{
			sprintf(score_affiche, "%d", tab_scores[choix*5+i][0]);
			texte = TTF_RenderText_Blended(police, score_affiche, couleur);
			position_score.x = position_score.x + (position_score.w - texte->w)/2;
			SDL_BlitSurface(texte, NULL, ecran, &position_score);
			position_score.y += 92; 
		}
		if (tab_scores[choix*5+i][1] != -1)
		{
			strcpy(joueur_affiche, pseudos_joueurs[tab_scores[choix*5+i][1]]);
			texte = TTF_RenderText_Blended(police, joueur_affiche, couleur);
			position_joueur.x = position_joueur.x + (position_joueur.w - texte->w)/2;
			SDL_BlitSurface(texte, NULL, ecran, &position_joueur);
			position_joueur.y += 92;
		}
	}
	SDL_Flip(ecran);

	// Boucle événementielle
	SDL_Event event;
	int continuer = 1;
	while (continuer)
	{	
		position_score.x = 110;
		position_score.y = 105;
		position_score.w = 170;
		position_score.h = 80;
		position_joueur.x = 295;
		position_joueur.y = 105;
		position_joueur.w = 270;
		position_joueur.h = 80;
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_LEFT:
					case SDLK_UP:
						Mix_PlayChannel(-1, curseur, 0);
						choix = ((choix-1)%4 + 4)%4;
						SDL_BlitSurface(scores[choix], NULL, ecran, &position);

						// Affichage des scores du monde choisi
						for (i=0; i<5; i++)
						{
							if (tab_scores[choix*5+i][0] != 9999)
							{
								sprintf(score_affiche, "%d", tab_scores[choix*5+i][0]);
								texte = TTF_RenderText_Blended(police, score_affiche, couleur);
								position_score.x = position_score.x + (position_score.w - texte->w)/2;
								SDL_BlitSurface(texte, NULL, ecran, &position_score);
								position_score.y += 92; 
							}
							if (tab_scores[choix*5+i][1] != -1)
							{
								strcpy(joueur_affiche, pseudos_joueurs[tab_scores[choix*5+i][1]]);
								texte = TTF_RenderText_Blended(police, joueur_affiche, couleur);
								position_joueur.x = position_joueur.x + (position_joueur.w - texte->w)/2;
								SDL_BlitSurface(texte, NULL, ecran, &position_joueur);
								position_joueur.y += 92;
							}
						position_score.x = 110;
						position_score.w = 170;
						position_score.h = 80;
						position_joueur.x = 295;
						position_joueur.w = 270;
						position_joueur.h = 80;
						}
						SDL_Flip(ecran);
						break;
					case SDLK_RIGHT:
					case SDLK_DOWN:
						Mix_PlayChannel(-1, curseur, 0);
						choix = (choix + 1)%4;
						SDL_BlitSurface(scores[choix], NULL, ecran, &position);

						// Affichage des scores du monde choisi
						for (i=0; i<5; i++)
						{
							if (tab_scores[choix*5+i][0] != 9999)
							{
								sprintf(score_affiche, "%d", tab_scores[choix*5+i][0]);
								texte = TTF_RenderText_Blended(police, score_affiche, couleur);
								position_score.x = position_score.x + (position_score.w - texte->w)/2;
								SDL_BlitSurface(texte, NULL, ecran, &position_score);
								position_score.y += 92;
							}
							if (tab_scores[choix*5+i][1] != -1)
							{
								strcpy(joueur_affiche, pseudos_joueurs[tab_scores[choix*5+i][1]]);
								texte = TTF_RenderText_Blended(police, joueur_affiche, couleur);
								position_joueur.x = position_joueur.x + (position_joueur.w - texte->w)/2;
								SDL_BlitSurface(texte, NULL, ecran, &position_joueur);
								position_joueur.y += 92;
							}
						position_score.x = 110;
						position_score.w = 170;
						position_score.h = 80;
						position_joueur.x = 295;
						position_joueur.w = 270;
						position_joueur.h = 80;
						}
						SDL_Flip(ecran);
						break;
					case SDLK_ESCAPE:
					case SDLK_q:
						continuer = 0;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}

	// Libération des surfaces
	for (i=0; i<4; i++) SDL_FreeSurface(scores[i]);
	SDL_FreeSurface(texte);

	// Fermeture de la police
	TTF_CloseFont(police);

	// Retour au menu
	return;
}


void afficherMenu(SDL_Surface *ecran)
{
	// Initialisation de la surface
	SDL_Surface *menu = NULL;

	// Chargement de la surface
	menu = IMG_Load("data/images/menu/menu_1.gif");

	// Affichage de la surface
	SDL_Rect position;
	position.x = 0;
	position.y = 0;
	SDL_BlitSurface(menu, NULL, ecran, &position);
	SDL_Flip(ecran);

	// Libération de la surface
	SDL_FreeSurface(menu);
}


int menuQuestion(SDL_Surface *ecran)
{
	// Initialisation des surfaces
    SDL_Surface *menu[6] = {NULL};

	// Chargement des surfaces
	menu[0] = IMG_Load("data/images/menu/menu_1.gif"); // Nouvelle partie
	menu[1] = IMG_Load("data/images/menu/menu_2.gif"); // Charger une partie
	menu[2] = IMG_Load("data/images/menu/menu_3.gif"); // Editer un niveau
	menu[3] = IMG_Load("data/images/menu/menu_4.gif"); // Mode multijoueur
	menu[4] = IMG_Load("data/images/menu/menu_5.gif"); // Consulter les scores
	menu[5] = IMG_Load("data/images/menu/menu_6.gif"); // Quitter
	
	// Initialisation des effets sonores
	Mix_Chunk *curseur = NULL;
	Mix_Chunk *valider = NULL;

	// Chargement des effets sonores
	curseur = Mix_LoadWAV("data/son/menu/curseur.wav");
	valider = Mix_LoadWAV("data/son/menu/valider.wav");
	
	// Boucle événementielle
	int cm = 0;
	int continuer = 1;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;
	SDL_Event event;
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
						cm = ((cm-1 % 6) + 6)%6;
						
						// Lecture du bruitage
						Mix_PlayChannel(-1, curseur, 0);

						// Affichage de la surface
						SDL_BlitSurface(menu[cm], NULL, ecran, &position);
						SDL_Flip(ecran);

						break;
					case SDLK_DOWN:
						cm = (cm+1)%6;

						// Lecture du bruitage
						Mix_PlayChannel(-1, curseur, 0);
						
						// Affichage de la surface
						SDL_BlitSurface(menu[cm], NULL, ecran, &position); 
						SDL_Flip(ecran);

						break;
					case SDLK_RETURN:
						// Lecture du bruitage
						Mix_PlayChannel(-1, valider, 0);
						SDL_Delay(600);

						continuer = 0;
						break;
					default:
						break;
				}
				break;
		}
	}

	// Libération des surfaces
	int i=0;
	while (i<6)
	{
		SDL_FreeSurface(menu[i]);
		i++;
	}

	// Libération des effets sonores
	Mix_FreeChunk(curseur);
	Mix_FreeChunk(valider);

	return cm;
}


void boucleMenu(SDL_Surface *ecran)
{
    int cm;
	while(1)
    {
		afficherMenu(ecran);
		cm = menuQuestion(ecran);
		switch (cm)
		{
			case 0: // Nouvelle partie
				nouvellePartie(ecran);
				break;
			case 1: // Charger une partie
				chargerPartie(ecran);
				break;
			case 2: // Editer un niveau
				editerNiveau(ecran);
				break;
			case 3: // Mode multijoueur
				break;
			case 4: // Consulter les scores
				consulterScores(ecran);
				break;
			case 5: // Quitter
				return;
		}
	}
}

