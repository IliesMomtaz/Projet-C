#include <stdio.h>
#include <unistd.h> 
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

#include "menu.h"
#include "jouer.h"
#include "afficher_map.h"
#include "map.h"
#include "Vehicule.h"

void afficher_map(void){
    for (int y = 0; y < map_hauteur; y++) {
        printf("%s\n", map[y]);
    }
}

void afficher_vehicules(VEHICULE* head) 
{
    VEHICULE *courant = head;
    
    while (courant != NULL) {
        
        // On vérifie que le véhicule est actif
        if (courant->etat == '1') {
            
            // Pour chaque ligne de la carrosserie (ici 4 lignes)
            for (int i = 0; i < 4; i++) {
                
                // Positionnement du curseur (y + i pour la ligne de la carrosserie, x pour la colonne)
                // Le format est \033[LIGNE;COLONNEf ou H
                // Note : Les coordonnées ANSI commencent à 1, 1 (pas 0, 0)
                printf("\033[%d;%dH", courant->posy + i + 1, courant->posx + 1);
                
                // Affichage de la ligne de carrosserie
                printf("%s", courant->Carrosserie[i]);
            }
            
            // On passe au véhicule suivant
            courant = courant->NXT;
        }
    }
    
    // Après avoir dessiné tous les véhicules, on repositionne le curseur
    // en bas de la map pour les logs ou pour éviter de dessiner au milieu de l'écran.
    printf("\033[%d;%dH", map_hauteur + 2, 0); 
}