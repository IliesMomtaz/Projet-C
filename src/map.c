#include <stdio.h>
#include <string.h>
#include "map.h"

char map[MAX_HAUTEUR][MAX_LARGEUR];
int map_largeur = 0;
int map_hauteur = 0;

void chargement_map(void)
{
    FILE *f = fopen("sprite/map_bk3.txt", "r");
    if (!f) {
        perror("Impossible d'ouvrir map");
        return;
    }

    map_hauteur = 0;
    map_largeur = 0;

    while (map_hauteur < MAX_HAUTEUR &&
           fgets(map[map_hauteur], MAX_LARGEUR, f) != NULL) {

        int len = strlen(map[map_hauteur]);

        // Enlever \n et \r éventuels
        while (len > 0 && (map[map_hauteur][len - 1] == '\n' ||
                           map[map_hauteur][len - 1] == '\r')) {
            map[map_hauteur][len - 1] = '\0';
            len--;
        }

        if (len > map_largeur) {
            map_largeur = len;
        }

        if (len == 0) continue;

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