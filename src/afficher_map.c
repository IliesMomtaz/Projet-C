#include <stdio.h>
#include <unistd.h> 
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

#include "menu.h"
#include "jouer.h"
#include "afficher_map.h"




void afficher_map(void){
    FILE *f = fopen("sprite/map.txt", "r");
    if (f == NULL) {
        perror("Erreur ouverture sprite/map.txt");
        return;
    }
    
    char ligne[256];
    while (fgets(ligne, sizeof(ligne), f) != NULL){
        printf("%s", ligne);
    }
    fclose(f);

    //fflush(stdout);
    //printf("\n\n appuyez sur une touche pour continuer \n");
    //getchar();
    //getchar();
}