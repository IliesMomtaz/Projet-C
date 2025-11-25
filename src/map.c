#include <stdio.h>
#include <string.h>
#include "map.h"

char map[MAX_HAUTEUR][MAX_LARGEUR];
int map_largeur = 0;
int map_hauteur = 0;

void chargement_map(void) {
    FILE *f = fopen("sprite/map.txt", "r");
    if (f == NULL) {
        perror("Erreur ouverture sprite/map.txt");
        return;
    }

    char ligne[300];
    int y = 0;
    map_largeur = 0;

    while (y < MAX_HAUTEUR && fgets(ligne, sizeof(ligne), f) != NULL) {
        // on enlève juste le '\n' de fin de ligne
        size_t len = strcspn(ligne, "\n");
        ligne[len] = '\0';

        // on copie TOUTE la ligne dans map[y]
        strncpy(map[y], ligne, MAX_LARGEUR - 1);
        map[y][MAX_LARGEUR - 1] = '\0';  // sécurité

        if ((int)len > map_largeur)
            map_largeur = (int)len;

        y++;
    }

    map_hauteur = y;
    fclose(f);
}





/*
void display_map() {}
void entree(int *x, int *y) {}
void sortie(int *x, int *y) {}
int access(int x, int y) {}
*/