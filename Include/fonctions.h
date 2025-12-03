#ifndef FONCTIONS_H
#define FONCTIONS_H


int is_free(int x, int y, int l, int h);
void free_area(int x, int y, int l, int h);
void occupy_area(int x, int y, int l, int h);
VEHICULE* vehicle_create(char direction);
void add_vehicle(VEHICULE** head, VEHICULE* v);

#endif




