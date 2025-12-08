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

// Affiche le fond de la carte (murs, routes vides)
void afficher_map(void){
    for (int y = 0; y < map_hauteur; y++) {
        printf("%s\n", map[y]);
    }
}

// Affiche les véhicules par-dessus la carte
void afficher_vehicules(VEHICULE* head) 
{
    VEHICULE *courant = head;
    
    while (courant != NULL) {
        
        if (courant->etat == '1') {
            
            // CORRECTION IMPORTANTE : Utilisation de HAUTEUR_VEHICULE 
            // au lieu de "4" en dur pour supporter la taille 1x1.
            for (int i = 0; i < HAUTEUR_VEHICULE; i++) {
                
                // +1 car les coordonnées console (ANSI) commencent à 1,1
                printf("\033[%d;%dH", courant->posy + i + 1, courant->posx + 1);
                
                printf("%s", courant->Carrosserie[i]);
            }
            
            courant = courant->NXT;
        }
    }
    
    // Repositionne le curseur en bas de la map pour ne pas écrire par-dessus
    printf("\033[%d;%dH", map_hauteur + 2, 0); 
}