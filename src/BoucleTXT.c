#include <stdlib.h>
#include <stdio.h>

#include "Menu.h"
 

void test(){
	printf("Oui.\n");
}


int main(){
	Menu m;
	menuInit(&m);
	menuAjouterLigne(&m, "Nouvelle partie", test);
	menuAjouterLigne(&m, "Charger une partie", test);
	menuAjouterLigne(&m, "Quitter", test);
	menuBoucle(&m);
	menuLibere(&m);
	return 0;
}
