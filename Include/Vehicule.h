#ifndef VEHICULE_H
#define VEHICULE_H

#include <stdio.h>


typedef struct voiture VEHICULE;

struct voiture
{
    char direction;
    int posx;
    int posy;
    int vitesse;
    char alignement;
    char type;
    char Carrosserie[4][30];
    int code_couleur;
    char etat;
    unsigned long int tps;
    struct voiture *NXT;
};

#define LARGEUR_VEHICULE 3
#define HAUTEUR_VEHICULE 4

void move_vehicle(VEHICULE *v);
void controler_vehicule_manuel(VEHICULE *v, char key);

#endif