#include <stdio.h>
#include "menu.h"
#include "fonctions.h" // Pour utiliser key_pressed

void affichage_menu(void)
{
    // 1. On efface l'écran pour un affichage propre
    printf("\033[2J\033[H");

    // 2. On essaie d'ouvrir le fichier (Mets le bon chemin ici !)
    // Si ton fichier est juste à côté de l'exécutable, mets juste "menu.txt"
    FILE *f = fopen("sprite/menu.txt", "r");
    if (f != NULL) {
        char ligne[256];
        printf("\033[34m"); // Couleur bleu pour le menu
        while (fgets(ligne, sizeof(ligne), f)) {
            printf("%s", ligne);
        }
        printf("\033[0m"); // Reset couleur
        fclose(f);
    } else {
        printf("Erreur : impossible d'ouvrir le fichier menu.txt\n");
    }
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