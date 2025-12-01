//structure donnée dans l'énoncé
typedef struct voiture VEHICULE;
struct voiture
{
char direction ; /*N => Nord, S => Sud, E => EST, O => OUEST*/
int posx; /*Position courante coin haut gauche x de la voiture*/
int posy; /*Position courante coin haut gauche y de la voiture*/
int vitesse; /*Vitesse du véhicule*/
char alignement; /*’g’=>gauche ou ’d’=>droite*/
char type; /*’v’=>voiture, ’c’=>camion, etc.*/
char Carrosserie [4][30]; /*Carrosserie de la voiture, servira pour
l’affichage du véhicule à tout moment*/
int code_couleur; /*Code couleur de la voiture à utiliser lors de
l’affichage*/
char etat; /*État du véhicule : ’1’ => actif et ’0’ => inactif*/
unsigned long int tps;/*pour stocker le temps passé dans le parking*/
struct voiture * NXT; /*Pointeur vers une prochaine voiture,
nécessaire pour la liste chaînée*/
/*Vous pouvez rajouter d’autres variables si nécessaire */
};




void move_vehicle(VEHICULE* v) {


    int next_x = posx; // la prochaine case est la position actuelle pour l'instant
    int next_y = posy;

    if (v.direction == 'E') {
        
        next_x += v.vitesse // on fait +1 ou -1 à la position selon l'orientation et la vitesse

    }

        if (v.direction == 'O') {
        
        next_x -= v.vitesse

    }

        if (v.direction == 'N') {
        
        next_y += v.vitesse
    }

            if (v.direction == 'S') {
        
        next_x -= v.vitesse
    }


    if is_free(next_x, next_y, largeur, hauteur){ // si cest libre devant (pas d'obstacle)

        free_area(v.posx, v.posy, largeur, hauteur) //on libère l'ancienne position

        v.posx = nex_x; //on incrémente la position actuelle à la nouvelle position
        v.posy = next_y;

        occupy_area(v->posx, v->posy, LARGEUR, HAUTEUR); // la nouvelle place est occupée
    }

    else {
        printf("il y a un obstacle");
    }

}



int is free(int x, int y, int l, int h) { //implementation de is_free (à mettre où??)

    for (int i = 0; i<h; i ++) {//boucle hauteur h
        for (int j = 0; j < l; j++){ //boucle largeur l

            if (grid[y+i][x+j] != 0) return 0 //voir implementation tableau;
        }
    }

return 1;

}
