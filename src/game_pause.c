#include <stdio.h>
#include <unistd.h> 
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

#include "menu.h"
#include "game_pause.h"

void game_pause(char *statut, char resultat, int *compteur, int *temps){
    if(*statut == 'J'){
        printf("\033[2J\033[H");
        if(resultat == 'P' || resultat == 'p'){
            *statut = 'P';
            printf("\033[2J\033[H");
            printf("=============LE JEU EST EN PAUSE============\n");

        }
        (*compteur)++;
        if((*compteur) % 60 == 0){
            (*temps)++;
        }
        usleep(16000);
        printf("Compteur = %d\n", *compteur);
        printf("Temps écoulé : %d secondes\n", *temps);
    }

    if(*statut == 'P'){
        if(resultat == 'P' || resultat == 'p'){
            *statut = 'J';
            printf("\033[2J\033[H");
            printf("=============LE JEU REPREND============\n");
            resultat=0;
        }
    }
}