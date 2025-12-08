#include <stdio.h>
#include <unistd.h> 
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

#include "menu.h"
#include "game_pause.h"
#include "afficher_map.h"

// game_pause.c
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
            return; 
        }
        
        (*compteur)++;
        if ((*compteur) % 60 == 0) (*temps)++;

        // CORRECTION VITESSE :
        // 16000 = trop rapide (~60 images/sec)
        // 100000 = plus lent (~10 images/sec), la voiture sera contrôlable
        usleep(100000); 
    }
    else if (*statut == 'P') {
        if (resultat == 'P' || resultat == 'p') {
            *statut = 'J';
            printf("\033[2J\033[H");
            afficher_map();
            printf("\033[2J\033[H");
        }
    }
}
