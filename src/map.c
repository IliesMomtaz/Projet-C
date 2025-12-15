#include <stdio.h>
#include <string.h>
#include "map.h"
//Ilies
char map[MAX_HAUTEUR][MAX_LARGEUR];
int grid[MAX_HAUTEUR][MAX_LARGEUR]; 

int map_largeur = 0;
int map_hauteur = 0;

// charge la map depuis map9.txt
void chargement_map(void) 
{
    FILE *f = fopen("sprite/map9.txt", "r");
    if (!f) {
        perror("Impossible d'ouvrir map");
        return;
    }

    map_hauteur = 0;
    map_largeur = 0;

    //initialize la grille
    for (int y = 0; y < MAX_HAUTEUR; y++) {
        for (int x = 0; x < MAX_LARGEUR; x++) {
            grid[y][x] = 2; // Par défaut, tout est bloqué
            map[y][x] = ' '; 
        }
    }

    char ligne[1024];

    // lecture ligne par ligne
    while (map_hauteur < MAX_HAUTEUR && fgets(ligne, sizeof(ligne), f) != NULL) {
        int len = strlen(ligne);
        
        while (len > 0 && (ligne[len - 1] == '\n' || ligne[len - 1] == '\r')) {
            ligne[--len] = '\0';
        }

        if (len >= MAX_LARGEUR) len = MAX_LARGEUR - 1;
        strncpy(map[map_hauteur], ligne, len);
        map[map_hauteur][len] = '\0'; 
        
        if (len > map_largeur) map_largeur = len;

        // setup de la grille decollision 
        for (int x = 0; x < len; x++) {
            char c = map[map_hauteur][x];
            // zones libres
            if (c == ' ' || c == '<' || c == '>' || c == '.' || c == '|' || c == '+') {
                grid[map_hauteur][x] = 0; // LIBRE
            } 
            else {
                // zones bloquées
                grid[map_hauteur][x] = 2; // MUR
            }
        }
        map_hauteur++;
    }
    fclose(f);

    // On nettoie les murs invisibles
    
    int y_debut_allee = 12;
    int y_fin_allee = 23;
    
    for (int y = y_debut_allee; y <= y_fin_allee; y++) {
        for (int x = 2; x < MAX_LARGEUR; x++) {

            // Si ce n'est pas un mur ou une bordure, on le met libre
            if (map[y][x] != '#' && map[y][x] != '-') {
                grid[y][x] = 0; 
            }
        }
    }}
