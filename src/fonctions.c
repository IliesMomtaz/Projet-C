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

// verifie si une zone est libre (on retourne 0) ou occupée (on retourne 1)
int is_free(int x, int y, int l, int h) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < l; j++) {
            if (y + i < 0 || y + i >= MAX_HAUTEUR || x + j < 0 || x + j >= MAX_LARGEUR) return 0;
            if (grid[y + i][x + j] != 0) return 0;
        }
    }	
    return 1;
}

// libère une zone (met à 0 dans la grille)
void free_area(int x, int y, int l, int h) {
    for (int i = 0; i < h; i++){
        for (int j = 0; j < l; j++){
            if (y + i >= 0 && y + i < MAX_HAUTEUR && x + j >= 0 && x + j < MAX_LARGEUR) grid[y + i][x + j] = 0; 
        }
    }
}

// occupe une zone (met à 1 dans la grille)
void occupy_area(int x, int y, int l, int h) {
    for (int i = 0; i < h; i++){
        for (int j = 0; j < l; j++){
            if (y + i >= 0 && y + i < MAX_HAUTEUR && x + j >= 0 && x + j < MAX_LARGEUR) grid[y + i][x + j] = 1; 
        }
    }
}

// charge le sprite du véhicule en fonction sa direction
void charger_sprite(VEHICULE *v) {
    // initialise des lignes à vide
    for(int i=0; i<6; i++) strcpy(v->Carrosserie[i], "");

    if (v->direction == 'E') { // sprite horizontal est
        v->w = 9; v->h = 3;
        strncpy(v->Carrosserie[0], "┌─┬───┼─┐", 40);
        strncpy(v->Carrosserie[1], "│ │|||│ │", 40);
        strncpy(v->Carrosserie[2], "└─┴───┼─┘", 40);
    }
    else if (v->direction == 'O') { // sprite horizontal ouest
        v->w = 9; v->h = 3;
        strncpy(v->Carrosserie[0], "┌─┼───┬─┐", 40);
        strncpy(v->Carrosserie[1], "│ │|||│ │", 40);
        strncpy(v->Carrosserie[2], "└─┼───┴─┘", 40);
    }
    else if (v->direction == 'N') { // sprite vertical nord
        v->w = 6; v->h = 5;
        strncpy(v->Carrosserie[0], "┌────┐", 40);
        strncpy(v->Carrosserie[1], "┼────┼", 40);
        strncpy(v->Carrosserie[2], "│====│", 40);
        strncpy(v->Carrosserie[3], "├────┤", 40);
        strncpy(v->Carrosserie[4], "└────┘", 40);
    }
    else if (v->direction == 'S') { // sprite vertical sud
        v->w = 6; v->h = 5;
        strncpy(v->Carrosserie[0], "┌────┐", 40);
        strncpy(v->Carrosserie[1], "├────┤", 40);
        strncpy(v->Carrosserie[2], "│====│", 40);
        strncpy(v->Carrosserie[3], "┼────┼", 40);
        strncpy(v->Carrosserie[4], "└────┘", 40);
    }
}

// crée un nouveau véhicule avec des valeurs par défaut
VEHICULE* create_vehicle(char direction, int vitesse, char type){
    VEHICULE* v = malloc(sizeof(VEHICULE));
    if (v == NULL) return NULL;

    v->posx = 0; v->posy = 0;
    v->direction = direction;
    v->vitesse = vitesse;
    v->type = type;
    v->alignement = 'g';
    v->etat = '1';
    v->tps = 0;
    v->timer_attente = 0;
    v->code_couleur = 31 + (rand() % 6); // Couleurs ANSI de 31 à 36
    v->NXT = NULL;

    // Charge le bon sprite dès le début
    charger_sprite(v);

    return v;
}

// ajoute un véhicule au début de la liste chaînée
void add_vehicle(VEHICULE** head, VEHICULE* v){
    if (v == NULL) return;
    v->NXT = *head;
    *head = v;
}

char key_pressed(void) {
    struct termios oldterm, newterm;
    int oldfd; char c, result = 0;
    tcgetattr (STDIN_FILENO, &oldterm);
    newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
    oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
    c = getchar();
    tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
    fcntl (STDIN_FILENO, F_SETFL, oldfd);
    if (c != EOF) { ungetc(c, stdin); result = getchar(); }
    return result;
}