// jouer.c
#include <stdio.h>
#include <unistd.h> 
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

#include "menu.h"
#include "jouer.h"
#include "afficher_map.h"
#include "map.h"
#include "fonctions.h"
#include "Vehicule.h"

extern VEHICULE* g_list_vehicules;
char mode_jeu = '1';
//quand on fait cet appel on lance une partie :
void jouer(char *statut, char resultat)
{
    if (resultat == '1' || resultat == '2') {
        mode_jeu = resultat;    // on mémorise le mode choisi

        *statut = 'J';

        printf("\033[2J\033[H");  
        chargement_map();          
        afficher_map();            

        printf("\nMode choisi : %c (1 = fluide, 2 = chargé)\n", mode_jeu);
    }
}

//fonction qui nous génére (juste ne printf pour l'instant) les voitures en fonction du mode
//fonction qui nous génére (juste ne printf pour l'instant) les voitures en fonction du mode
static void gerer_generation_vehicules(char mode, int compteur)
{
    // MODIFICATION : Si une voiture existe déjà, on arrête tout de suite.
    // Comme ça, il n'y en aura qu'une seule sur la carte.
    if (g_list_vehicules != NULL) {
        return; 
    }

    // Si on arrive ici, c'est qu'il n'y a pas de voiture, donc on la crée.
    // (Peu importe le mode 1 ou 2 pour l'instant)
    
    VEHICULE* new_v = create_vehicle('E', 1, 'v'); // Crée un véhicule se dirigeant vers l'Est
    if (new_v != NULL) {
        // Coordonnées de test (milieu de l'allée)
        new_v->posx = 30; 
        new_v->posy = 12; 
        
        add_vehicle(&g_list_vehicules, new_v);
        
        // On marque la zone occupée sur la grille
        occupy_area(new_v->posx, new_v->posy, LARGEUR_VEHICULE, HAUTEUR_VEHICULE);
    }
}

//temps de fermeture des barrieres
static void gerer_barrieres(int temps)
{
    if (temps % 5 == 0) {
        // ici toutes les 5 sec on fait changer l'état de la barriere en ouvert ou fermé 
    
        //printf("[DEBUG] Mise à jour barrières (temps=%d s)\n", temps);
    }
}

//ici c'est la fonction pour voir si une voiture es ta la borne, le paimenet etc
static void gerer_paiement(void){

}

//Condition de fin de partie 
static int verifier_fin_partie(int temps)
{
   
    if (temps >= 600) {
        printf("\n===== FIN DE PARTIE (temps >= 60 s) =====\n");
        return 1;
    }
    return 0;
}

// MISE À JOUR : La fonction accepte maintenant la touche pressée 'key'
void maj_jeu(char *statut, char mode, int compteur, int temps, char key)
{
    gerer_generation_vehicules(mode, compteur);

    // LOGIQUE DE CONTRÔLE : Si une touche directionnelle est pressée et qu'un véhicule existe
    if (g_list_vehicules != NULL && 
        (key == 'z' || key == 'Z' || key == 'd' || key == 'D' || 
         key == 'q' || key == 'Q' || key == 's' || key == 'S')) {
             
        // On contrôle le premier véhicule de la liste
        controler_vehicule_manuel(g_list_vehicules, key);
    }

    // 1. Déplacement de tous les véhicules
    VEHICULE *courant = g_list_vehicules;
    while (courant != NULL) {
        move_vehicle(courant);
        courant = courant->NXT;
    }

    gerer_barrieres(temps);
    gerer_paiement();

    if (verifier_fin_partie(temps)) {
        *statut = 'M';
    }

    // Réaffichage de la map et des voitures 
    printf("\033[2J\033[H"); 
    afficher_map();
    
    afficher_vehicules(g_list_vehicules);
}