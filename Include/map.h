#ifndef MAP_H
#define MAP_H

#define MAX_HAUTEUR 200
#define MAX_LARGEUR 300

extern char map[MAX_HAUTEUR][MAX_LARGEUR];
extern int map_largeur;
extern int map_hauteur;

void chargement_map(void);

#endif
