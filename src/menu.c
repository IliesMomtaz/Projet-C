#include <stdio.h>

#include "menu.h"


void affichage_menu(void)
{
    printf("\n");
    printf("======================================================\n");
    printf("                Simulateur de parking                 \n");
    printf("======================================================\n");
    printf("\n");
    printf("[1] Activation du mode Fluide\n");
    printf("\n");
    printf("[2] Activation du mode Chargé\n");
    printf("\n");
    printf("[q] Quitter\n");
    printf("\n");
}

void menu(char *statut, char resultat){
    (*statut) = 'M';
    affichage_menu();
    resultat = 0; // je remet a chaque fois a 0 pcq sinon pour le pause/play ca posait probleme
}

