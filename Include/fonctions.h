#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "Vehicule.h" // Important pour connaître la structure VEHICULE


// Prototypes
int is_free(int x, int y, int l, int h);
void free_area(int x, int y, int l, int h);
void occupy_area(int x, int y, int l, int h);

// --- NOUVEAU ---
void charger_sprite(VEHICULE *v); // Indispensable pour l'IA qui tourne
// ----------------

char key_pressed(void);

#endif