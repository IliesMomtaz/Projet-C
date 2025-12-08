#include "fonctions.h"
#include "map.h"
#include "Vehicule.h"

#include <stdlib.h> 
#include <string.h>
#include <stdio.h>
#include <unistd.h> 
#include <termios.h>
#include <fcntl.h>

extern int grid[MAX_HAUTEUR][MAX_LARGEUR];
VEHICULE* g_list_vehicules = NULL;

// tester si l'endroit est libre
int is_free(int x, int y, int l, int h) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < l; j++) {
            if (y + i < 0 || y + i >= MAX_HAUTEUR || x + j < 0 || x + j >= MAX_LARGEUR) {
                return 0; 
            }
            if (grid[y + i][x + j] != 0) {
                return 0; 
            }
        }
    }	
    return 1;
}

// marquer libre l'endroit que la voiture vient de quitter
void free_area(int x, int y, int l, int h) {
    for (int i = 0; i < h; i++){
        for (int j = 0; j < l; j++){
            if (y + i >= 0 && y + i < MAX_HAUTEUR && x + j >= 0 && x + j < MAX_LARGEUR) {
                grid[y + i][x + j] = 0; 
            }
        }
    }
}

// marquer occupé l'endroit où la voiture vient d'arriver
void occupy_area(int x, int y, int l, int h) {
    for (int i = 0; i < h; i++){
        for (int j = 0; j < l; j++){
            if (y + i >= 0 && y + i < MAX_HAUTEUR && x + j >= 0 && x + j < MAX_LARGEUR) {
                grid[y + i][x + j] = 1; 
            }
        }
    }
}

// créer un vehicule et initialiser attributs
VEHICULE* create_vehicle(char direction, int vitesse, char type){
    VEHICULE* v = malloc(sizeof(VEHICULE));
    if (v == NULL) return NULL;

    v->posx = 0;
    v->posy = 0;
    v->direction = direction;
    v->vitesse = vitesse;
    v->type = type;
    v->alignement = 'g';
    v->etat = '1';
    v->tps = 0;
    v->NXT = NULL;

    // MODIFICATION ICI : On met juste un caractère (par exemple 'V' ou ce que vous voulez)
    strncpy(v->Carrosserie[0], "V", 29); 
    
    // On vide les autres lignes pour être propre (optionnel mais conseillé)
    strcpy(v->Carrosserie[1], "");
    strcpy(v->Carrosserie[2], "");
    strcpy(v->Carrosserie[3], "");

    return v;
}

void add_vehicle(VEHICULE** head, VEHICULE* v){
    if (v == NULL) return;
    v->NXT = *head;
    *head = v;
}

// DÉPLACEMENT DE LA FONCTION key_pressed ICI
char key_pressed(void)
{
    struct termios oldterm, newterm;
    int oldfd; 
    char c, result = 0;
    
    tcgetattr (STDIN_FILENO, &oldterm);
    newterm = oldterm; 
    newterm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
    oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
    c = getchar();
    tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
    fcntl (STDIN_FILENO, F_SETFL, oldfd);

    if (c != EOF) {
        ungetc(c, stdin); 
        result = getchar();
    }
    return result;
}