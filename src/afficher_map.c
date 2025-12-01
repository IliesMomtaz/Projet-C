#include <ncurses.h> // <-- Nouvelle inclusion pour Ncurses
#include <stdio.h>
#include <unistd.h> 
#include <string.h>

#include "afficher_map.h"
#include "map.h"

void afficher_map(void){
    
    // Ncurses est basé sur des coordonnées (y, x).
    // On efface l'écran (Ncurses gère cela mieux que l'échappement ANSI)
    clear(); 
    
    // Parcourir la carte et l'afficher ligne par ligne et colonne par colonne
    for (int y = 0; y < map_hauteur; y++) {
        // L'affichage avec mvprintw est plus performant et fiable
        // pour les caractères étendus dans un environnement Ncurses bien configuré.
        mvprintw(y, 0, "%s", map[y]);
    }

    // Afficher les changements à l'écran
    refresh();
}