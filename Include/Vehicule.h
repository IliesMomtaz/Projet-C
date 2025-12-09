#ifndef VEHICULE_H
#define VEHICULE_H

// Définition de la structure VEHICULE
typedef struct vehicule {
    int posx;
    int posy;
    int w;
    int h;
    char direction; // 'N', 'S', 'E', 'O'
    int vitesse;
    char type;
    char alignement;
    char etat;      // '1'=Joueur, '2'=Garée, '3'=Sortie (IA)
    int tps;        // Compteur pour le mouvement (vitesse)
    
    // --- NOUVEAU ---
    int timer_attente; // Compteur pour savoir quand quitter le parking
    // ----------------

    char Carrosserie[6][40]; // Le dessin de la voiture
    struct vehicule * NXT;   // Pointeur vers la voiture suivante (liste chainée)
} VEHICULE;

// Prototypes des fonctions liées aux véhicules
VEHICULE* create_vehicle(char direction, int vitesse, char type);
void add_vehicle(VEHICULE** head, VEHICULE* v);
void move_vehicle(VEHICULE *v);
void controler_vehicule_manuel(VEHICULE *v, char key);

// --- NOUVELLES FONCTIONS IA ---
void gerer_ia_sortie(VEHICULE *v);
void despawn_vehicule(VEHICULE *v);

#endif