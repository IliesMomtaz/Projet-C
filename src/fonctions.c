#include "fonctions.h"
#include "map.h"
#include "Vehicule.h"

#include <stdlib.h> 
#include <string.h>

extern int grid[MAX_HAUTEUR][MAX_LARGEUR];
VEHICULE* g_list_vehicules = NULL;

// tester si l'endroit est libre :
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

// marquer libre l'endroit que la voiture vient de quitter :
void free_area(int x, int y, int l, int h) {
    for (int i = 0; i < h; i++){
        for (int j = 0; j < l; j++){
            if (y + i >= 0 && y + i < MAX_HAUTEUR && x + j >= 0 && x + j < MAX_LARGEUR) {
                grid[y + i][x + j] = 0; 
            }
        }
    }
}

// marquer occupé l'endroit où la voiture vient d'arriver :
void occupy_area(int x, int y, int l, int h) {
    for (int i = 0; i < h; i++){
        for (int j = 0; j < l; j++){
            if (y + i >= 0 && y + i < MAX_HAUTEUR && x + j >= 0 && x + j < MAX_LARGEUR) {
                grid[y + i][x + j] = 1;   // ou 3, mais il faut être cohérent partout
            }
        }
    }
}

#include <stdio.h>
#include <string.h>

int load_sprite(const char *filename, char carrosserie[4][64])
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Erreur ouverture sprite voiture");
        return -1;
    }

    char ligne[128];
    int i = 0;

    while (i < 4 && fgets(ligne, sizeof(ligne), f)) {
        // enlever le \n
        size_t len = strcspn(ligne, "\r\n");
        ligne[len] = '\0';

        strncpy(carrosserie[i], ligne, 63);
        carrosserie[i][63] = '\0';   // sécurité
        i++;
    }

    // si tu n'as que 3 lignes dans le fichier, tu vides la 4e
    while (i < 4) {
        carrosserie[i][0] = '\0';
        i++;
    }

    fclose(f);
    return 0;
}

// créer un vehicule et initialiser attributs :
VEHICULE* create_vehicle(char direction, int vitesse, char type){

    VEHICULE* v = malloc(sizeof(VEHICULE));
    if (v == NULL) {
        return NULL;
    }

    v->posx = 0;
    v->posy = 0;
    v->direction = direction;
    v->vitesse = vitesse;
    v->type = type;
    v->alignement = 'g';
    v->etat = '1';
    v->tps = 0;
    v->NXT = NULL;

    int ret = load_sprite("sprite/sprite-voiture.txt", v->Carrosserie);
    printf("[DEBUG] ret load_sprite = %d\n", ret);

    if (ret != 0) {
        strcpy(v->Carrosserie[0], "########");
        strcpy(v->Carrosserie[1], "########");
        strcpy(v->Carrosserie[2], "########");
        strcpy(v->Carrosserie[3], "########");
    }
    return v;
}

// ajouter un vehicule à la liste chainée :
void add_vehicle(VEHICULE** head, VEHICULE* v){

    if (v == NULL) return;
    v->NXT = *head;
    *head = v;
}
