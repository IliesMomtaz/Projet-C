#include "Vehicule.h"
#include "map.h"
#include "fonctions.h"

void move_vehicle(VEHICULE *v)
{
    if (v == NULL) return; 

    int next_x = v->posx; 
    int next_y = v->posy;

    // Calcul de la prochaine position
    if (v->direction == 'E') {
        next_x += v->vitesse;
    } else if (v->direction == 'O') {
        next_x -= v->vitesse;
    } else if (v->direction == 'N') {
        next_y -= v->vitesse;
    } else if (v->direction == 'S') {
        next_y += v->vitesse;
    }

    // --- CORRECTION MAJEURE ANTI-BLOCAGE ---
    // 1. On retire D'ABORD la voiture de sa position actuelle.
    //    Sinon, elle se considère elle-même comme un obstacle !
    free_area(v->posx, v->posy, LARGEUR_VEHICULE, HAUTEUR_VEHICULE); 

    // 2. Maintenant on vérifie si la place est libre
    if (is_free(next_x, next_y, LARGEUR_VEHICULE, HAUTEUR_VEHICULE)) {
        // C'est libre : on valide le déplacement
        v->posx = next_x; 
        v->posy = next_y;
    } 
    // Si c'est pas libre, v->posx/posy ne changent pas, la voiture reste sur place.

    // 3. On réaffiche la voiture (à la nouvelle ou l'ancienne position)
    occupy_area(v->posx, v->posy, LARGEUR_VEHICULE, HAUTEUR_VEHICULE); 
}

void controler_vehicule_manuel(VEHICULE *v, char key) 
{
    if (v == NULL) return;
    
    if (key == 'z' || key == 'Z') {
        v->direction = 'N';
    } else if (key == 'd' || key == 'D') {
        v->direction = 'E';
    } else if (key == 'q' || key == 'Q') {
        v->direction = 'O';
    } else if (key == 's' || key == 'S') {
        v->direction = 'S';
    }
}