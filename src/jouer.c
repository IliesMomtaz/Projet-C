#include <stdio.h>
#include <unistd.h> 
#include "menu.h"
#include "jouer.h"
#include "afficher_map.h"
#include "map.h"
#include "fonctions.h"
#include "Vehicule.h"

//Ilies
extern VEHICULE* g_list_vehicules;
char mode_jeu = '1';


void jouer(char *statut, char resultat)
{
    if (resultat == '1' || resultat == '2') {
        mode_jeu = resultat;
        *statut = 'J';
        printf("\033[2J\033[H");  
        chargement_map();          
        afficher_map();            
        printf("\nMode: %c\n", mode_jeu);
    }
}

static void gerer_generation_vehicules(char mode, int compteur)
{
    (void)mode;
    (void)compteur;

    // verification de l'existance d'une voiture active 
    VEHICULE *parcours = g_list_vehicules;
    while (parcours != NULL) {
        if (parcours->etat == '1') return;
        parcours = parcours->NXT;
    }

    // Création d'une nouvelle voiture
    VEHICULE* new_v = create_vehicle('O', 1, 'v'); 

    if (new_v != NULL) {
        new_v->posx = 63; // Colonne (X) demandée
        new_v->posy = 13; // Ligne (Y) demandée
        
        new_v->vitesse = 0; // À l'arrêt au spawn

        add_vehicle(&g_list_vehicules, new_v);
        occupy_area(new_v->posx, new_v->posy, new_v->w, new_v->h);
    }
}

static int verifier_fin_partie(int temps)
{
    if (temps >= 600) return 1;
    return 0;
}

static void gerer_barrieres(int temps) { (void)temps; } // Ajout pour éviter warning
static void gerer_paiement(void) {}

// Mise à jour principale du jeu à chaque cycle
void maj_jeu(char *statut, char mode, int compteur, int temps, char key)
{
    // On gère l'apparition des nouvelles voitures
    gerer_generation_vehicules(mode, compteur);

    VEHICULE *parcours = g_list_vehicules;
    VEHICULE *active_car = NULL;

    while (parcours != NULL) {
        //Voiture active 
        if (parcours->etat == '1') {
            active_car = parcours;
            // Gestion touches joueur
            if (key == ' ') {
                active_car->etat = '2'; // On se gare
                active_car->vitesse = 0;
                active_car->timer_attente = 0; // On lance le chrono !
            }
            else if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {
                controler_vehicule_manuel(active_car, key);
            }
            // Déplacement automatique (seulement pour la voiture active)
            move_vehicle(active_car);
        }

        // Voiture garée 
        else if (parcours->etat == '2') {
            parcours->timer_attente++;
            // attend 100 cycles avant de partir
            if (parcours->timer_attente > 100) {
                parcours->etat = '3'; // elle sort
            }
        }

        //Voiture sort
        else if (parcours->etat == '3') {
            gerer_ia_sortie(parcours);
        }

        parcours = parcours->NXT;
    }


    // Gestion fin de partie, Barrières, paiement
    if (verifier_fin_partie(temps)) *statut = 'M';
    gerer_barrieres(temps);
    gerer_paiement();

    // Affichage
    printf("\033[2J\033[H"); 
    afficher_map();
    afficher_vehicules(g_list_vehicules);
}
