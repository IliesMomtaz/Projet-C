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

void afficher_map(void){
    for (int y = 0; y < map_hauteur; y++) {
        printf("%s\n", map[y]);
    }
}