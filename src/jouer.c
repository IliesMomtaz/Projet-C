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
static void gerer_generation_vehicules(char mode, int compteur)
{
    if (mode == '1') {
        // mode fluide
        if (compteur % 180 == 0) { //toutes les 180 itérations
            printf("[DEBUG] Génération véhicule (mode FLUIDE) - compteur=%d\n", compteur);
        }
    } else if (mode == '2') {
        // mode chargé : spawn plus souvent
        if (compteur % 60 == 0) {
            printf("[DEBUG] Génération véhicule (mode CHARGE) - compteur=%d\n", compteur);
        }
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

void maj_jeu(char mode, int compteur, int temps)
{
    gerer_generation_vehicules(mode, compteur);

    gerer_barrieres(temps);

    gerer_paiement();

    if (verifier_fin_partie(temps)) {
        //on mettra a jours la variable statut piur que ca quitte 
    }
}