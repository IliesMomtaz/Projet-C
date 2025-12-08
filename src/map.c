#include <stdio.h>
#include <string.h>
#include "map.h"

char map[MAX_HAUTEUR][MAX_LARGEUR];
int grid[MAX_HAUTEUR][MAX_LARGEUR]; 

int map_largeur = 0;
int map_hauteur = 0;

void chargement_map(void) 
{
    FILE *f = fopen("sprite/map9.txt", "r");
    if (!f) {
        perror("Impossible d'ouvrir map");
        return;
    }

    map_hauteur = 0;
    map_largeur = 0;

    // 1. On remplit la grille de "2" (MURS) par défaut
    // Comme ça, le vide est dangereux !
    for (int y = 0; y < MAX_HAUTEUR; y++) {
        for (int x = 0; x < MAX_LARGEUR; x++) {
            grid[y][x] = 2; 
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

        if (len >= MAX_LARGEUR) len = MAX_LARGEUR - 1;
        strncpy(map[map_hauteur], ligne, len);
        map[map_hauteur][len] = '\0';
        if (len > map_largeur) map_largeur = len;

        // --- NOUVELLE LOGIQUE : TOUT EST UN MUR SAUF LA ROUTE ---
        for (int x = 0; x < len; x++) {
            char c = map[map_hauteur][x];

            // LISTE DES ZONES SÛRES (Où on a le droit de rouler)
            // ' ' = Route
            // '|' = Ligne de parking (on peut rouler dessus pour se garer)
            // '-' = Pointillés
            // '<' et '>' = Flèches au sol
            // '.' = Décoration sol
            if (c == ' ' || c == '|' || c == '-' || c == '_' || 
                c == '<' || c == '>' || c == '.') {
                
                grid[map_hauteur][x] = 0; // C'est LIBRE (Route)
            
            } else {
                // Tout le reste (#, +, █, ║, A, Z...) devient un MUR
                grid[map_hauteur][x] = 2; // OBSTACLE
            }
        }
        map_hauteur++;
    }
    fclose(f);
}