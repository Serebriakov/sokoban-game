#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "Menu.h"


void menuInit(Menu *m){
    m->nb_lignes = 0;
}


void menuAjouterLigne(Menu *m, char texte[64], MenuFonction fonction){ 
	assert(m->nb_lignes<32);
    strcpy(m->lignes[m->nb_lignes].texte, texte);
    m->lignes[m->nb_lignes].commande = fonction;
    m->nb_lignes++;
}


void menuAffiche(const Menu *m){
    int i;
    for (i=0; i<m->nb_lignes; i++){
        printf("%d : %s\n", i, m->lignes[m->nb_lignes].texte);
    }
	printf("Entrez votre choix :\n");
	fflush(stdout);
}


int menuChoix(const Menu *m){
    int num_choix;
    int ok = 0;
	char txt[32];
    while (!ok){
        if (scanf("%d", &num_choix)!=1) scanf("%s", txt);
        if ((num_choix < 0) || (num_choix >= m->nb_lignes)){
            printf("Choix non valide !\n");
			fflush(stdout);
			printf("Entrez votre choix :\n");
		}
        else ok = 1;
		fflush(stdout);
    }
    return num_choix;
}


void menuBoucle(Menu *m){
    int fin = 0;
    while (!fin){
        menuAffiche(m);
        int num_choix = menuChoix(m);
        m->lignes[num_choix].commande();
    }
}


void menuLibere(Menu *m){
    m->nb_lignes = 0;
}
