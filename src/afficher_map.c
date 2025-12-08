#include <stdio.h>
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
        if (courant->etat == '1') {
            for (int i = 0; i < HAUTEUR_VEHICULE; i++) {
                printf("\033[%d;%dH", courant->posy + i + 1, courant->posx + 1);
                printf("%s", courant->Carrosserie[i]);
            }
            courant = courant->NXT;
        }
    }
    printf("\033[%d;%dH", map_hauteur + 2, 0); 
}