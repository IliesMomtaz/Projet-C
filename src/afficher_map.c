#include <stdio.h>
#include "afficher_map.h"
#include "map.h"
#include "Vehicule.h"

// 1. Fonction qui affiche le fond (Murs et routes)
// C'est celle qui manquait et qui créait ton erreur !
void afficher_map(void){
    for (int y = 0; y < map_hauteur; y++) {
        printf("%s\n", map[y]);
    }
}

// 2. Fonction qui affiche les voitures (Active + Garées)
void afficher_vehicules(VEHICULE* head) 
{
    VEHICULE *courant = head;
    
    while (courant != NULL) {
        // --- CORRECTION ICI ---
        // On affiche si : Active ('1') OU Garée ('2') OU En Sortie ('3')
        if (courant->etat == '1' || courant->etat == '2' || courant->etat == '3') {
            
            // On boucle sur la hauteur actuelle du véhicule
            for (int i = 0; i < courant->h; i++) {
                
                // Positionnement du curseur (+1 pour coord ANSI)
                printf("\033[%d;%dH", courant->posy + i + 1, courant->posx + 1);
                
                // Affichage de la ligne du sprite
                printf("%s", courant->Carrosserie[i]);
            }
        }
        courant = courant->NXT;
    }
    
    // On remet le curseur en bas pour ne pas casser l'affichage
    printf("\033[%d;%dH", map_hauteur + 2, 0); 
}