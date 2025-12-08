#include "fonctions.h"
#include "map.h"
#include "Vehicule.h"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h> 
#include <termios.h>
#include <fcntl.h>

extern int grid[MAX_HAUTEUR][MAX_LARGEUR];
VEHICULE* g_list_vehicules = NULL;

// Vérifie si l'endroit est libre
int is_free(int x, int y, int l, int h) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < l; j++) {
            if (y + i < 0 || y + i >= MAX_HAUTEUR || x + j < 0 || x + j >= MAX_LARGEUR) return 0;
            if (grid[y + i][x + j] != 0) return 0;
        }
    }	
    return 1;
}

void free_area(int x, int y, int l, int h) {
    for (int i = 0; i < h; i++){
        for (int j = 0; j < l; j++){
            if (y + i >= 0 && y + i < MAX_HAUTEUR && x + j >= 0 && x + j < MAX_LARGEUR) grid[y + i][x + j] = 0; 
        }
    }
}

void occupy_area(int x, int y, int l, int h) {
    for (int i = 0; i < h; i++){
        for (int j = 0; j < l; j++){
            if (y + i >= 0 && y + i < MAX_HAUTEUR && x + j >= 0 && x + j < MAX_LARGEUR) grid[y + i][x + j] = 1; 
        }
    }
}

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

    // --- DESSIN SÉCURISÉ (40 carac) ---
    strncpy(v->Carrosserie[0], "┌─┬───┼─┐", 40);
    v->Carrosserie[0][39] = '\0';
    
    strncpy(v->Carrosserie[1], "│ │|||│ │", 40);
    v->Carrosserie[1][39] = '\0'; 
    
    strncpy(v->Carrosserie[2], "└─┴───┼─┘", 40);
    v->Carrosserie[2][39] = '\0'; 

    strcpy(v->Carrosserie[3], "");

    return v;
}

void add_vehicle(VEHICULE** head, VEHICULE* v){
    if (v == NULL) return;
    v->NXT = *head;
    *head = v;
}

// --- TA FONCTION D'ORIGINE (RESTAURÉE) ---
char key_pressed()
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