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
if (c == '#') {
                printf("\033[34m%c\033[0m", c); // 34 = Bleu
            }
            // SI C'EST UNE BORDURE (-, |, 1, 2, 3, 4) -> On le met en CYAN
            else if (c == '-'  || (c >= '1' && c <= '4')) {
                // Tu peux aussi utiliser les caractères spéciaux ici
                // Exemple : if (c=='-') printf("\u2500");
                
                printf("\033[1;36m%c\033[0m", c); // 36 = Cyan
            }
            // SI C'EST DE L'HERBE OU DECO -> VERT
            else if (c == '>' || c == '|') {
                printf("\033[1;35m%c\033[0m", c); // 35 = Magenta
            }
            // SINON (Route, vide) -> BLANC (Par défaut)
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
