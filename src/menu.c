#include <stdio.h>
#include "menu.h"
#include "fonctions.h" // Pour utiliser key_pressed

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

char menu()
{
    affichage_menu();
    char choix = 0;
    while (choix != '1' && choix != '2' && choix != 'q') {
        choix = key_pressed();
    }
    return choix;
}