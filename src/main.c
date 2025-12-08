#include <stdio.h>
#include <unistd.h> 
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

#include "menu.h"
#include "afficher_map.h"
#include "game_pause.h"
#include "jouer.h"
#include "fonctions.h" // Inclusion nécessaire

int main(void)
{
    char statut = 'M'; 
    int compteur = 0;  
    int temps = 0;     
    
    while (statut != 'Q') {
        if (statut == 'M') {
            char choix = menu();
            if (choix == '1' || choix == '2') {
                jouer(&statut, choix);
            } else if (choix == 'x' || choix == 'X') {
                statut = 'Q';         
            }
        }
        else if (statut == 'J' || statut == 'P') {
            char resultat = key_pressed(); // Appel depuis fonctions.c

            if (resultat == 'M' || resultat == 'm') {
                statut = 'M';
                printf("\033[2J\033[H");
                continue;
            }
            if (resultat == 'X' || resultat == 'x') {
                statut = 'Q';
                continue;
            }

            game_pause(&statut, resultat, &compteur, &temps);

            if (statut == 'J') {
                maj_jeu(&statut, mode_jeu, compteur, temps, resultat);     
            }
        }
    }
    return 0;
}