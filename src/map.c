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

    // 1. INITIALISATION
    for (int y = 0; y < MAX_HAUTEUR; y++) {
        for (int x = 0; x < MAX_LARGEUR; x++) {
            grid[y][x] = 2; // Par défaut, tout est bloqué
            map[y][x] = ' '; 
        }
    }

    char ligne[1024];

    // 2. LECTURE DU FICHIER
    while (map_hauteur < MAX_HAUTEUR && fgets(ligne, sizeof(ligne), f) != NULL) {
        int len = strlen(ligne);
        
        while (len > 0 && (ligne[len - 1] == '\n' || ligne[len - 1] == '\r')) {
            ligne[--len] = '\0';
        }

        if (len >= MAX_LARGEUR) len = MAX_LARGEUR - 1;
        strncpy(map[map_hauteur], ligne, len);
        map[map_hauteur][len] = '\0'; 
        
        if (len > map_largeur) map_largeur = len;

        // --- LOGIQUE DE COLLISION ---
        for (int x = 0; x < len; x++) {
            char c = map[map_hauteur][x];
            
            // J'ai gardé '|' (traversable) mais ENLEVÉ '-' (bloquant)
            // '+' est souvent utilisé pour les coins, je le laisse traversable, 
            // mais tu peux l'enlever si tu veux que les coins bloquent.
            if (c == ' ' || c == '<' || c == '>' || c == '.' || c == '|' || c == '+') {
                grid[map_hauteur][x] = 0; // LIBRE
            } 
            else {
                // Ici tombent : '#', et maintenant '-'
                grid[map_hauteur][x] = 2; // MUR
            }
        }
        map_hauteur++;
    }
    fclose(f);

    // ============================================================
    // 3. ZONE DE SÉCURITÉ (L'ALLÉE CENTRALE)
    // ============================================================
    // On nettoie les murs invisibles, MAIS on respecte ta règle sur les tirets '-'
    
    int y_debut_allee = 12;
    int y_fin_allee = 23;
    
    for (int y = y_debut_allee; y <= y_fin_allee; y++) {
        for (int x = 2; x < MAX_LARGEUR; x++) {
            
            // On force le passage SEULEMENT si ce n'est pas un obstacle majeur
            // Si c'est un Mur '#' OU un Tiret '-', on ne touche pas (ça reste bloqué)
            if (map[y][x] != '#' && map[y][x] != '-') {
                grid[y][x] = 0; 
            }
        }
    }
}