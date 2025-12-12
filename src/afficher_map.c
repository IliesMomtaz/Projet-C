#include <stdio.h>
#include <string.h>
#include "afficher_map.h"
#include "map.h"
#include "Vehicule.h"

void afficher_map(void)
{
    for (int y = 0; y < map_hauteur; y++) 
    {
        for (int x = 0; x < strlen(map[y]); x++) 
        {
            char c = map[y][x];

            if (c == '#') { 
                // Affiche '│' en bleu clair
                printf("\033[1;36m\u2502\033[0m");
            } 
            else if (c == '-') {
                // Affiche '─'
                printf("\033[1;36m\u2500\033[0m");
            }
            else if (c == '1') {
                // Coin haut à gauche : ┌
                printf("\033[1;36m\u250C\033[0m"); 
            }
            else if (c == '2') {
                // Coin Haut-Droite : ┐
                printf("\033[1;36m\u2510\033[0m"); 
            }
            else if (c == '3') {
                // Coin Bas-Gauche : └
                printf("\033[1;36m\u2514\033[0m"); 
            }
            else if (c == '4') {
                // Coin Bas-Droite : ┘
                printf("\033[1;36m\u2518\033[0m");
            }
            else if (c == '|' || c == '>') {
                printf("\033[1;35m%c\033[0m", c);// violet
            }
            // Sinon par défaut
            else {
                printf("%c", c);
            }
        
        }
        printf("\n"); 
    }
}


void afficher_vehicules(VEHICULE* head) 
{
    VEHICULE *courant = head;
    while (courant != NULL) 
    {
        // etat 1 : active, etat 2 garée, etat 3 sortante
        if (courant->etat != '0') 
        {
            
            for (int i = 0; i < courant->h; i++) 
            { // courant->h (hauteur dynamique)
                // On place le curseur
                printf("\033[%d;%dH", courant->posy + i + 1, courant->posx + 1);
                
                // couleur du véhicule
                printf("\033[%dm", courant->code_couleur); 
                
                // dessin de la ligne de la carrosserie
                printf("%s", courant->Carrosserie[i]);
                
                // reset couleur
                printf("\033[0m");
            }
        }
        courant = courant->NXT;
    }
    // On remet le curseur en bas pour ne pas gêner
    printf("\033[%d;%dH", map_hauteur + 2, 0); 
}
