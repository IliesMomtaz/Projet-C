#include <stdio.h>
#include <stdlib.h>
#include "Vehicule.h"
#include "map.h"
#include "fonctions.h"

// Contrôle manuel (Conversion touches -> Direction)
void controler_vehicule_manuel(VEHICULE *v, char key) 
{
    if (v == NULL) return;
    
    // On accepte les flèches (renvoyées comme A, B, C, D par key_pressed)
    if (key == 'A') v->direction = 'N';      // Haut
    else if (key == 'B') v->direction = 'S'; // Bas
    else if (key == 'C') v->direction = 'E'; // Droite
    else if (key == 'D') v->direction = 'O'; // Gauche
}

// Déplacement avec correction de l'AUTO-COLLISION
void move_vehicle(VEHICULE *v)
{
    if (v == NULL) return;

    // Gestion vitesse
    v->tps++;
    if (v->tps < v->vitesse) return; 
    v->tps = 0;

    int newx = v->posx;
    int newy = v->posy;

    // Calcul de la future position
    switch (v->direction) {
        case 'N': newy--; break;
        case 'S': newy++; break;
        case 'E': newx++; break;
        case 'O': newx--; break;
    }

    // --- CORRECTION MAJEURE ICI ---
    
    // 1. On "soulève" la voiture (on efface sa position actuelle de la grille)
    // Sinon, elle se détecte elle-même comme un obstacle !
    free_area(v->posx, v->posy, LARGEUR_VEHICULE, HAUTEUR_VEHICULE);

    // 2. On vérifie si la destination est libre (Murs ou AUTRES voitures)
    if (is_free(newx, newy, LARGEUR_VEHICULE, HAUTEUR_VEHICULE)) {
        // C'est libre : on valide le déplacement
        v->posx = newx;
        v->posy = newy;
    } 
    // Sinon (Mur), on ne change pas v->posx/v->posy, elle reste sur place.

    // 3. On "repose" la voiture sur la grille (à la nouvelle ou l'ancienne position)
    occupy_area(v->posx, v->posy, LARGEUR_VEHICULE, HAUTEUR_VEHICULE);
}