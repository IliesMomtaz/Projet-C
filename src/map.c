#include <stdio.h>
#include <string.h>
#include "map.h"

char map[MAX_HAUTEUR][MAX_LARGEUR];
int map_largeur = 0;
int map_hauteur = 0;

void chargement_map(void)
{
    FILE *f = fopen("sprite/map.txt", "r");
    if (!f) {
        perror("Impossible d'ouvrir map");
        return;
    }

    map_hauteur = 0;

    while (fgets(map[map_hauteur], MAX_LARGEUR, f) != NULL) {
        int len = strlen(map[map_hauteur]);

        // enlever le \n final
        if (len > 0 && map[map_hauteur][len - 1] == '\n') {
            map[map_hauteur][len - 1] = '\0';
        }

        map_hauteur++;
    }

    fclose(f);
}







/*
void display_map() {}
void entree(int *x, int *y) {}
void sortie(int *x, int *y) {}
int access(int x, int y) {}
*/