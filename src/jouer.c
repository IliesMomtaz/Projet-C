#include <stdio.h>
#include <unistd.h> 
#include "menu.h"
#include "jouer.h"
#include "afficher_map.h"
#include "map.h"
#include "fonctions.h"
#include "Vehicule.h"

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

    if (g_list_vehicules != NULL) return; 

    VEHICULE* new_v = create_vehicle('E', 1, 'v');
    if (new_v != NULL) {
        
        // --- COORDONNÉES CORRIGÉES ---
        new_v->posx = 9;   // Tout à gauche
        new_v->posy = 20;  // <-- ON REMONTE ICI (Avant c'était 17)
        
        // Vitesse
        new_v->vitesse = 1; 

        add_vehicle(&g_list_vehicules, new_v);
        occupy_area(new_v->posx, new_v->posy, LARGEUR_VEHICULE, HAUTEUR_VEHICULE);
    }
}

static int verifier_fin_partie(int temps)
{
    if (temps >= 600) return 1;
    return 0;
}

static void gerer_barrieres(int temps) { (void)temps; } // Ajout pour éviter warning
static void gerer_paiement(void) {}

void maj_jeu(char *statut, char mode, int compteur, int temps, char key)
{
    gerer_generation_vehicules(mode, compteur);

    // 1. Contrôle (Flèches)
    if (g_list_vehicules != NULL && 
        (key == 'A' || key == 'B' || key == 'C' || key == 'D')) {
        controler_vehicule_manuel(g_list_vehicules, key);
    }

    // 2. Mouvement
    VEHICULE *courant = g_list_vehicules;
    while (courant != NULL) {
        move_vehicle(courant);
        courant = courant->NXT;
    }

    if (verifier_fin_partie(temps)) *statut = 'M';
    
    // Appel des fonctions vides pour éviter warnings
    gerer_barrieres(temps);
    gerer_paiement();

    // 3. Affichage
    printf("\033[2J\033[H"); 
    afficher_map();
    afficher_vehicules(g_list_vehicules);
}