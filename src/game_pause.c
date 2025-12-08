#include <stdio.h>
#include <unistd.h> 
#include "menu.h"
#include "game_pause.h"
#include "afficher_map.h"

void game_pause(char *statut, char resultat, int *compteur, int *temps){
    if (*statut == 'J') {
        if (resultat == 'P' || resultat == 'p') {
            *statut = 'P';
            printf("\033[2J\033[H");
            printf("============= PAUSE ============\n");
            return; 
        }
        
        (*compteur)++;
        if ((*compteur) % 60 == 0) (*temps)++;
        usleep(100000); 
    }
    else if (*statut == 'P') {
        if (resultat == 'P' || resultat == 'p') {
            *statut = 'J';
            printf("\033[2J\033[H");
            afficher_map();
        }
    }
}