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

    // 1. On vérifie si une voiture roule déjà (le code que je t'ai donné avant)
    VEHICULE *parcours = g_list_vehicules;
    while (parcours != NULL) {
        if (parcours->etat == '1') return;
        parcours = parcours->NXT;
    }

    // 2. CRÉATION AVEC NOUVELLES COORDONNÉES
    // Attention : J'ai changé 'E' (Est) en 'O' (Ouest) pour qu'elle regarde vers la gauche !
    // Si tu veux qu'elle regarde vers la droite, remets 'E'.
    VEHICULE* new_v = create_vehicle('E', 1, 'v'); 

    if (new_v != NULL) {
        new_v->posx = 3; // Colonne (X) demandée
        new_v->posy = 14; // Ligne (Y) demandée
        
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

void maj_jeu(char *statut, char mode, int compteur, int temps, char key)
{
    // --- CALCUL DU TEMPS D'ATTENTE ---
    // Votre boucle tourne à env. 0.1s (usleep 100000)
    int duree_attente;

    if (mode == '1') {
        duree_attente = 100; // 100 * 0.1s = 10 secondes
    } 
    else {
        duree_attente = 50;  // 70 * 0.1s = 7 secondes
    }
    // ---------------------------------

    // 1. On gère l'apparition des nouvelles voitures
    gerer_generation_vehicules(mode, compteur);

    VEHICULE *parcours = g_list_vehicules;
    VEHICULE *active_car = NULL;

    // --- BOUCLE PRINCIPALE SUR TOUTES LES VOITURES ---
    while (parcours != NULL) {
        
        // Cas 1 : La voiture du JOUEUR (Etat '1')
        if (parcours->etat == '1') {
            active_car = parcours;
            
            // --- C'EST ICI QUE LA VOITURE SE GARE ---
            if (key == ' ') {
                active_car->etat = '2'; // Passe en mode GARÉE
                active_car->vitesse = 0;
                active_car->timer_attente = 0; // On remet le chrono à 0
            }
            // ----------------------------------------
            
            else if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {
                controler_vehicule_manuel(active_car, key);
            }
            // Déplacement automatique (seulement pour la voiture active)
            move_vehicle(active_car);
        }

        // Cas 2 : Voiture GARÉE (Etat '2') -> Compte à rebours
        else if (parcours->etat == '2') {
            parcours->timer_attente++; // On augmente le compteur de 1 à chaque tour
            
            // Si on dépasse la durée définie (10s ou 7s), on passe en sortie
            if (parcours->timer_attente >= duree_attente) {
                parcours->etat = '3'; // C'est l'heure de partir !
            }
        }

        // Cas 3 : Voiture EN SORTIE (Etat '3') -> L'IA conduit vers la sortie
        else if (parcours->etat == '3') {
            gerer_ia_sortie(parcours);
        }

        parcours = parcours->NXT;
    }
    // -------------------------------------------------

    // Gestion fin de partie, Barrières, etc.
    if (verifier_fin_partie(temps)) *statut = 'M';
    gerer_barrieres(temps);
    gerer_paiement();

    // Affichage
    printf("\033[2J\033[H"); 
    afficher_map();
    afficher_vehicules(g_list_vehicules);
}