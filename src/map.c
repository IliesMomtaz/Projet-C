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

    // 1. Par sécurité, on remplit tout de MURS (2) au départ
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

        // --- LOGIQUE DE COLLISION STRICTE ---
        for (int x = 0; x < len; x++) {
            char c = map[map_hauteur][x];

            // LISTE DES ZONES AUTORISÉES (Seulement la route !)
            // Si c'est un espace ' ' OU une flèche '<' '>' OU un point '.', on roule.
            if (c == ' ' || c == '<' || c == '>' || c == '.') {
                
                grid[map_hauteur][x] = 0; // C'est LIBRE (0)
            
            } 
            // TOUT LE RESTE DEVIENT UN MUR (2)
            // Cela inclut :
            // '#' (Murs)
            // '+' (Coins)
            // '-' (Lignes horizontales)
            // '|' ou '│' (Lignes verticales)
            else {
                grid[map_hauteur][x] = 2; // C'est un OBSTACLE
            }
        }
        map_hauteur++;
    }
    fclose(f);
}