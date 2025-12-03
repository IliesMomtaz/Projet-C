#include "fonctions.h"
#include "map.h"

extern int grid[MAX_HAUTEUR][MAX_LARGEUR];

//tester si l'endroit est libre :
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

//marquer libre l'endroit que la voiture vient de quitter :
void free_area(int x, int y, int l, int h) {
	for (int i = x; i = x + l - 1){
	    for (int j = y; j = y + h - 1){
	        grid[i][j] = 0; 
	    }
	}
}

//marquer occupé l'endroit où la voiture vient d'arriver :
void occupy_area(int x, int y, int l, int h) {

	for (int i = x; i = x + l - 1){
		    for (int j = y; j = y + h - 1){
		        grid[i][j] = 3; //3 
			}
	}
}

//créer un vehicule et initialiser attributs :
VEHICLE* vehicle_create(char direction, int vitesse, char type){

    VEHICLE* v = malloc(sizeof());
    
    v->posx = 0;
	v->posy = 0;
    v->direction = direction;
    v->vitesse = vitesse;
    v->type = type;
    v->alignement = 'g';
    v->etat = '1';
    v->tps = 0;
    v-> NXT = NULL;

    //carroserie
    strcpy(v->Carrosserie[0], "########");
    strcpy(v->Carrosserie[1], "########");
    strcpy(v->Carrosserie[2], "########");
    strcpy(v->Carrosserie[3], "########");

    return v;

}

//ajouter un vehicule à la liste chainée :
void add_vehicle(VEHICLE** head, VEHICLE* v){

    if (v == NULL) return;
    v->NXT = *head;
    *head = v;
    
}

