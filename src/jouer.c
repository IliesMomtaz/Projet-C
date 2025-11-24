#include <stdio.h>
#include <unistd.h> 
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

#include "menu.h"
#include "jouer.h"
#include "afficher_map.h"

void jouer(char *statut, char resultat){

            if(resultat == '1' || resultat == '2'){
                (*statut) = 'J';
                
                if(resultat == '1'){
                    //activer le mode Fluide 
                    printf("\033[2J\033[H");
                    printf("Le Jeu a commencer !!\n");
                    afficher_map();
                    resultat=0;
                }
            if(resultat == '2'){
                //activer le mode Charger
                printf("\033[2J\033[H"); 
                printf("Le Jeu a commencer !!\n");
                afficher_map();
                resultat=0;
            }
        }
}
