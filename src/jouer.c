#include <stdio.h>
#include <unistd.h> 
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

#include "menu.h"
#include "jouer.h"
#include "afficher_map.h"
#include "map.h"


void jouer(char *statut, char resultat){

    if (resultat == '1' || resultat == '2') {
        *statut = 'J';

        printf("\033[2J\033[H");
        chargement_map();              
        printf("Le Jeu a commencer !!\n");
        afficher_map();               
        resultat = 0;
    }
}
