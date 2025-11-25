#include <stdio.h>
#include <unistd.h> 
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

#include "menu.h"
#include "game_pause.h"
#include "afficher_map.h"

void game_pause(char *statut, char resultat, int *compteur, int *temps){
    if (*statut == 'J') {
        if (resultat == 'P' || resultat == 'p') {
            *statut = 'P';

            printf("\033[2J\033[H");
            printf("=============LE JEU EST EN PAUSE============\n");
            return; // on sort tout de suite
        }
        // Jeu en cours : on avance le temps
        (*compteur)++;
        if ((*compteur) % 60 == 0) (*temps)++;
        usleep(16000);
        //printf("\033[2J\033[H");
        //printf("Compteur = %d\n", *compteur);
        //printf("Temps écoulé : %d secondes\n", *temps);
    }
    else if (*statut == 'P') {
        // En pause : on ne bouge pas compteur/temps
        if (resultat == 'P' || resultat == 'p') {
            *statut = 'J';
            printf("\033[2J\033[H");
            afficher_map();
            printf("\033[2J\033[H");
        }
    }
}

