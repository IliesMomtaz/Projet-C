#include <stdio.h>
#include <unistd.h> 
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

#include "menu.h"
#include "afficher_map.h"
#include "game_pause.h"
#include "jouer.h"

char key_pressed(void);

int main(void)
{
    char statut = 'M'; 
    int compteur = 0;  
    int temps = 0;     
    

    while (statut != 'Q') {

        if (statut == 'M') {
            char choix = menu();  // menu() affiche + lit la touche

            if (choix == '1' || choix == '2') {
                jouer(&statut, choix);  // lance la partie en mode choisi
            } else if (choix == 'q' || choix == 'Q') {
                statut = 'Q';         
            }
        }

        else if (statut == 'J' || statut == 'P') {
            char resultat = key_pressed();

            if (resultat == 'M' || resultat == 'm') {
                statut = 'M';
                printf("\033[2J\033[H");
                continue;
            }

            // Quitter le jeu
            if (resultat == 'Q' || resultat == 'q') {
                statut = 'Q';
                continue;
            }

            game_pause(&statut, resultat, &compteur, &temps);

            // Si on est bien en mode jeu on met à jour la logique
            if (statut == 'J') {
                maj_jeu(mode_jeu, compteur, temps);
            }
        }
    }
    return 0;
}

char key_pressed(void)
{
    struct termios oldterm, newterm;
    int oldfd; 
    char c, result = 0;
    
    tcgetattr (STDIN_FILENO, &oldterm);
    newterm = oldterm; 
    newterm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
    oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
    c = getchar();
    tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
    fcntl (STDIN_FILENO, F_SETFL, oldfd);

    if (c != EOF) {
        ungetc(c, stdin); 
        result = getchar();
    }
    return result;
}
