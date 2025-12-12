#include <stdio.h>
#include <stdlib.h>
#include "Vehicule.h"
#include "map.h"
#include "fonctions.h" 

// Gère le changement de direction et la rotation du sprite (Joueur)
void controler_vehicule_manuel(VEHICULE *v, char key) 
{
    if (v == NULL) return;
    
    char nouvelle_dir = v->direction;
    
    if (key == 'A') nouvelle_dir = 'N';      // Haut
    else if (key == 'B') nouvelle_dir = 'S'; // Bas
    else if (key == 'C') nouvelle_dir = 'E'; // Droite
    else if (key == 'D') nouvelle_dir = 'O'; // Gauche

    if (nouvelle_dir != v->direction) {
        free_area(v->posx, v->posy, v->w, v->h);

        // Calcul des nouvelles dimensions avant de valider
        int new_w = (nouvelle_dir == 'N' || nouvelle_dir == 'S') ? 6 : 9;
        int new_h = (nouvelle_dir == 'N' || nouvelle_dir == 'S') ? 5 : 3;

        if (is_free(v->posx, v->posy, new_w, new_h)) {
            v->direction = nouvelle_dir;
            charger_sprite(v); 
        }
        occupy_area(v->posx, v->posy, v->w, v->h);
    }
}

// Gère le déplacement (Avancer)
void move_vehicle(VEHICULE *v)
{
    if (v == NULL) return;

    // Gestion vitesse
    v->tps++;
    if (v->tps < v->vitesse) return; 
    v->tps = 0;

    int newx = v->posx;
    int newy = v->posy;

    switch (v->direction) {
        case 'N': newy--; break;
        case 'S': newy++; break;
        case 'E': newx++; break;
        case 'O': newx--; break;
    }

    free_area(v->posx, v->posy, v->w, v->h);

    if (is_free(newx, newy, v->w, v->h)) {
        v->posx = newx;
        v->posy = newy;
    } 

    occupy_area(v->posx, v->posy, v->w, v->h);
}

void despawn_vehicule(VEHICULE *v) {
    free_area(v->posx, v->posy, v->w, v->h); 
    v->etat = '0'; 
    v->posx = -100; 
}

// --- INTELLIGENCE ARTIFICIELLE : CONTOURNEMENT ---
void gerer_ia_sortie(VEHICULE *v) {
    if (v == NULL || v->etat != '3') return;

    // --- REPÈRES ---
    int Y_SORTIE = 14;   // Ligne de sortie
    int X_FIN = 140;     // Fin de la map
    int X_ALLEE = 42;    // Zone sûre à gauche
    // ----------------

    v->tps++;
    if (v->tps < 1) return; // Vitesse Max
    v->tps = 0;

    // 1. SI SORTI -> DESPAWN
    if (v->posx >= X_FIN) {
        despawn_vehicule(v);
        return;
    }

    // 2. CAS : ON EST ALIGNÉ SUR LA SORTIE (Y=17) -> ON FONCE
    if (v->posy == Y_SORTIE) {
        if (v->direction != 'E') {
            free_area(v->posx, v->posy, v->w, v->h);
            v->direction = 'E'; // Regarde à droite
            charger_sprite(v);
            occupy_area(v->posx, v->posy, v->w, v->h);
        }
        move_vehicle(v);
    }

    // 3. CAS : ON N'EST PAS ALIGNÉ -> IL FAUT MANOEUVRER
    else {
        
        // A. SI ON EST TROP À DROITE (Dans les places ou bloqué par le mur central)
        if (v->posx > X_ALLEE) {
            
            // On veut aller à GAUCHE (Ouest) pour rejoindre l'allée
            // MAIS on vérifie si on va taper un mur !
            
            free_area(v->posx, v->posy, v->w, v->h);
            int obstacle_a_gauche = !is_free(v->posx - 1, v->posy, 9, 3); // 9x3 = taille horizontale
            occupy_area(v->posx, v->posy, v->w, v->h);

            // SCÉNARIO 1 : La voie est libre à gauche
            if (!obstacle_a_gauche) {
                if (v->direction != 'O') {
                    free_area(v->posx, v->posy, v->w, v->h);
                    v->direction = 'O'; // On tourne à gauche
                    charger_sprite(v);
                    occupy_area(v->posx, v->posy, v->w, v->h);
                }
                move_vehicle(v);
            }
            
            // SCÉNARIO 2 : MUR EN FACE !! (C'est ton problème actuel)
            // La voiture veut aller à gauche mais tape le rectangle central.
            // -> SOLUTION : On force le contournement vers le BAS (Sud).
            else {
                // On vérifie si on peut descendre pour contourner
                free_area(v->posx, v->posy, v->w, v->h);
                int peut_descendre = is_free(v->posx, v->posy + 1, 6, 5); // 6x5 = taille verticale
                occupy_area(v->posx, v->posy, v->w, v->h);

                if (peut_descendre) {
                    if (v->direction != 'S') {
                        free_area(v->posx, v->posy, v->w, v->h);
                        v->direction = 'S'; // On tourne vers le bas
                        charger_sprite(v);
                        occupy_area(v->posx, v->posy, v->w, v->h);
                    }
                    move_vehicle(v);
                }
                // Si on ne peut pas descendre, on essaie de monter (Secours)
                else {
                    if (v->direction != 'N') {
                        free_area(v->posx, v->posy, v->w, v->h);
                        v->direction = 'N';
                        charger_sprite(v);
                        occupy_area(v->posx, v->posy, v->w, v->h);
                    }
                    move_vehicle(v);
                }
            }
        }

        // B. SI ON EST DANS L'ALLÉE CENTRALE (X <= 45) -> ON S'ALIGNE
        else {
            char dir_voulue = (v->posy < Y_SORTIE) ? 'S' : 'N';
            
            if (v->direction != dir_voulue) {
                free_area(v->posx, v->posy, v->w, v->h);
                if (is_free(v->posx, v->posy, 6, 5)) {
                    v->direction = dir_voulue;
                    charger_sprite(v);
                }
                occupy_area(v->posx, v->posy, v->w, v->h);
            }
            move_vehicle(v);
        }
    }
}