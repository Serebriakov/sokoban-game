#include <stdlib.h>

#ifdef JEU_TXT
#include "afficheTXT.h"
#include "menu.h"
#endif

#ifdef JEU_SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "afficheSDL.h"
#endif


int main(int argc, char *argv[])
{
#ifdef JEU_TXT
	// Initialisation du menu
	Menu m;
    menuInit(&m);

	// Construction du menu
    menuAjouterLigne(&m, "Nouvelle partie", nouvellePartie);
    menuAjouterLigne(&m, "Charger une partie", chargerPartie);
    menuAjouterLigne(&m, "Quitter", NULL);
    
	// Boucle principale du programme
    boucleMenu(&m);

	// Libération du menu
	menuLibere(&m);

    return EXIT_SUCCESS;
#endif


#ifdef JEU_SDL
	// Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);

	// Initialisation de SDL_Mixer
 	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_AllocateChannels(2);

	// Initialisation de SDL_TTF
	TTF_Init();
	
	// Icône de la fenêtre
	SDL_Surface *icone = NULL;
	icone = IMG_Load("data/images/icone.png");           
	SDL_WM_SetIcon(icone, NULL);
    SDL_FreeSurface(icone);

    // Dimensions et légende de la fenêtre
	SDL_Surface *ecran = NULL;
	ecran = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Sokoban Legends", "Sokoban Legends");

	// Masquage de la souris
	SDL_ShowCursor(SDL_DISABLE);

	// Boucle principale du programme
	boucleMenu(ecran);

	// Libération de TTF
	TTF_Quit();

	// Libération de SDL_Mixer
	Mix_CloseAudio();

	// Libération de SDL (libère aussi la surface ecran)
	SDL_Quit();

    return EXIT_SUCCESS;
#endif
}
