#include "Vehicule.h"
#include "map.h"
#include "fonctions.h"

void move_vehicle(VEHICULE *v)
{
    if (v == NULL) return; 

    int next_x = v->posx; 
    int next_y = v->posy;

    if (v->direction == 'E') {
        next_x += v->vitesse;
    } else if (v->direction == 'O') {
        next_x -= v->vitesse;
    } else if (v->direction == 'N') {
        next_y -= v->vitesse;
    } else if (v->direction == 'S') {
        next_y += v->vitesse;
    }

    if (is_free(next_x, next_y, LARGEUR_VEHICULE, HAUTEUR_VEHICULE)) {
        free_area(v->posx, v->posy, LARGEUR_VEHICULE, HAUTEUR_VEHICULE); 

        v->posx = next_x; 
        v->posy = next_y;

        occupy_area(v->posx, v->posy, LARGEUR_VEHICULE, HAUTEUR_VEHICULE); 

    } else {
        
    }
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