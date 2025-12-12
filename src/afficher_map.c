#include <stdio.h>
#include <string.h>
#include "afficher_map.h"
#include "map.h"
#include "Vehicule.h"

// 1. Fonction qui affiche le fond (Murs et routes)
// C'est celle qui manquait et qui créait ton erreur !
void afficher_map(void)
{
    for (int y = 0; y < map_hauteur; y++) 
    {
        for (int x = 0; x < strlen(map[y]); x++) 
        {
            char c = map[y][x];

            // Si c'est un mur (#) ou une bordure, on met en BLEU
            if (c == '#') { // 219 est le code du pavé plein (█) si utilisé
                printf("\033[1;36m\u2502\033[0m");
            } 
            else if (c == '-') {
                printf("\033[1;36m\u2500\033[0m"); // Affiche '─'
            }
            else if (c == '1') {
                // Coin Haut-Gauche : ┌
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
            else if (c == '1') {
                // Coin Haut-Gauche : ┌
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
            // Si c'est de l'herbe ou déco extérieure, on peut mettre en VERT par exemple
            else if (c == '|' || c == '>') {
                printf("\033[1;35m%c\033[0m", c);
            }
            // Sinon (la route, les lignes), on laisse en blanc par défaut
            else {
                printf("%c", c);
            }
        
        }
        printf("\n"); // Fin de la ligne
    }
}


// 2. Fonction qui affiche les voitures (Active + Garées)
void afficher_vehicules(VEHICULE* head) 
{
    VEHICULE *courant = head;
    while (courant != NULL) 
    {
        // On affiche si la voiture est active ('1'), garée ('2') ou sortante ('3')
        if (courant->etat != '0') 
        {
            
            for (int i = 0; i < courant->h; i++) 
            { // Utilise courant->h (hauteur dynamique)
                // 1. On place le curseur
                printf("\033[%d;%dH", courant->posy + i + 1, courant->posx + 1);
                
                // 2. On active la couleur de CE véhicule
                printf("\033[%dm", courant->code_couleur); 
                
                // 3. On dessine la ligne de carrosserie
                printf("%s", courant->Carrosserie[i]);
                
                // 4. On remet la couleur normale (RESET) pour ne pas colorier toute la suite
                printf("\033[0m");
            }
        }
        courant = courant->NXT;
    }
    // On remet le curseur en bas pour ne pas gêner
    printf("\033[%d;%dH", map_hauteur + 2, 0); 
}
