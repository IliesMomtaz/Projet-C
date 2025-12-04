#include "Vehicule.h"
#include "map.h"
#include "fonctions.h"
#include <string.h>

void move_vehicle(VEHICULE *v)
{
    if (!v || v->etat != '1') return;

    // taille du sprite
    int h = 4;                                   // 4 lignes
    int l = (int)strlen(v->Carrosserie[0]);      // largeur (nb de caractères)

    int dx = 0, dy = 0;

    switch (v->direction) {
        case 'E': dx = 1;  break;   // droite
        case 'O': dx = -1; break;   // gauche
        case 'S': dy = 1;  break;   // bas
        case 'N': dy = -1; break;   // haut
        default: return;
    }

    int new_x = v->posx + dx * v->vitesse;
    int new_y = v->posy + dy * v->vitesse;

    // libère l’ancienne zone dans la grille
    free_area(v->posx, v->posy, l, h);

    // vérifier si la nouvelle zone est libre
    if (is_free(new_x, new_y, l, h)) {
        // met à jour la position
        v->posx = new_x;
        v->posy = new_y;
    }
    else {
        // ici tu peux changer de direction si tu veux “rebondir”
        // exemple simple : faire demi-tour horizontal
        if (v->direction == 'E') v->direction = 'O';
        else if (v->direction == 'O') v->direction = 'E';
        else if (v->direction == 'N') v->direction = 'S';
        else if (v->direction == 'S') v->direction = 'N';
    }
    // On marque la zone finale (nouvelle ou ancienne si bloqué)
    occupy_area(v->posx, v->posy, l, h);
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

    printf("[DEBUG] key=%c, direction=%c\n", key, v->direction);

}