#include <stdio.h>
#include <string.h>
#include "map.h"

char map[MAX_HAUTEUR][MAX_LARGEUR];
int grid[MAX_HAUTEUR][MAX_LARGEUR]; // DEFINITION DE LA GRILLE DE COLLISION

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

    for (int y = 0; y < MAX_HAUTEUR; y++) {
        for (int x = 0; x < MAX_LARGEUR; x++) {
            grid[y][x] = 0; 
        }
    }
    
    //Lecture du fichier map
    while (map_hauteur < MAX_HAUTEUR &&
           fgets(map[map_hauteur], MAX_LARGEUR, f) != NULL) {

        int len = strlen(map[map_hauteur]);

        // Enlever \n et \r 
        while (len > 0 && (map[map_hauteur][len - 1] == '\n' ||
                           map[map_hauteur][len - 1] == '\r')) {
            map[map_hauteur][len - 1] = '\0';
            len--;
        }

        if (len > map_largeur) {
            map_largeur = len;
        }

        if (len == 0) continue;

        // 3. LOGIQUE P1 MANQUANTE :
        // Ici, la Personne 1 devrait parcourir la ligne lue (map[map_hauteur])
        // pour détecter les murs/obstacles et mettre à jour la grille 'grid'
        // Exemple : if (map[map_hauteur][x] == '#') grid[map_hauteur][x] = 2; // 2 = Mur

        map_hauteur++;
    }

    fclose(f);
}




