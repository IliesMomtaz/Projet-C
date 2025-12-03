#include "fonctions.h"
#include "map.h"

extern int grid[MAX_HAUTEUR][MAX_LARGEUR];

int is_free(int x, int y, int l, int h) { 

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < l; j++) {

            if (y + i < 0 || y + i >= MAX_HAUTEUR || x + j < 0 || x + j >= MAX_LARGEUR) {
                return 0; 
            }

            if (grid[y + i][x + j] != 0) {
                return 0; 
            }
        }
    }
    return 1;
}

void free_area(int x, int y, int l, int h) {
    // Implémentation Personne 2: définir grid[y+i][x+j] = 0
}

void occupy_area(int x, int y, int l, int h) {
    // Implémentation Personne 2: définir grid[y+i][x+j] = ID_VEHICULE
}