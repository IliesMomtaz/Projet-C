#include <stdio.h>
#include <string.h>
#include "map.h"

char map[MAX_HAUTEUR][MAX_LARGEUR];
int grid[MAX_HAUTEUR][MAX_LARGEUR]; 

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

    // Reset grille
    for (int y = 0; y < MAX_HAUTEUR; y++) {
        for (int x = 0; x < MAX_LARGEUR; x++) {
            grid[y][x] = 0; 
        }
    }

    char ligne[1024];

    while (map_hauteur < MAX_HAUTEUR && fgets(ligne, sizeof(ligne), f) != NULL) {
        int len = strlen(ligne);
        
        // Nettoyage fin de ligne
        while (len > 0 && (ligne[len - 1] == '\n' || ligne[len - 1] == '\r')) {
            ligne[--len] = '\0';
        }
        if (len == 0) continue; 

        // Copie visuelle
        if (len >= MAX_LARGEUR) len = MAX_LARGEUR - 1;
        strncpy(map[map_hauteur], ligne, len);
        map[map_hauteur][len] = '\0';
        if (len > map_largeur) map_largeur = len;

        // --- LOGIQUE DE COLLISION SIMPLE ET FIABLE ---
        for (int x = 0; x < len; x++) {
            char c = map[map_hauteur][x];

            // 1. CE QUI BLOQUE (MURS SOLIDES)
            // '#' : le contour du parking
            // '+' et '-' : les murets centraux (si tu veux qu'on puisse rouler dessus, retire-les d'ici)
            if (c == '#' || c == '+' || c == '-') {
                grid[map_hauteur][x] = 2; // OBSTACLE
            } 
            // 2. TOUT LE RESTE EST LIBRE
            // (Espaces, '|' pour se garer, '<', '>')
            else {
                grid[map_hauteur][x] = 0; // LIBRE
            }
        }
        // ---------------------------------------------
        map_hauteur++;
    }
    fclose(f);
}