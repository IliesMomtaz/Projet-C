#ifndef FONCTIONS_H
#define FONCTIONS_H


int is_free(int x, int y, int l, int h);
void free_area(int x, int y, int l, int h);
void occupy_area(int x, int y, int l, int h);
VEHICULE* create_vehicle(char direction, int vitesse, char type);
void add_vehicle(VEHICLE** head, VEHICLE* v);


#endif




