#ifndef VEHICULE_H
#define VEHICULE_H

// --- DIMENSIONS ---
#define LARGEUR_VEHICULE 9 
#define HAUTEUR_VEHICULE 3

typedef struct vehicule {
    int posx;
    int posy;
    char direction; // 'N', 'S', 'E', 'O'
    int vitesse;
    char type;      
    char alignement;
    char etat;
    int tps;
    
    // Taille mémoire augmentée pour supporter les caractères spéciaux
    char Carrosserie[4][50]; 

    struct vehicule *NXT;
} VEHICULE;

// --- PROTOTYPES AJOUTÉS (C'est ce qui manquait !) ---
void controler_vehicule_manuel(VEHICULE *v, char key);
void move_vehicle(VEHICULE *v);

#endif