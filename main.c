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

char key_pressed();

int main()
{
    affichage_menu();
    char statut = 'M'; // on va avoir trois états : M(Menu), J(Jouer), P(Pause) et Q(Quit)
    int compteur = 0; //ça va servir a par exemple au bout de 60 tours de bouvle on va faire spawn une voiture ou un truc de genre
    int temps = 0; //pour connaitre le vrai temps écoulé 
    
    while(statut != 'Q'){
        char resultat = key_pressed();

        if(resultat == 'M' || resultat == 'm'){ // Si pendant le jeu le joueur veut retourner dans le menu, en le remettant ici il le peut
            menu(&statut, resultat);
        }
        
        if(statut == 'M'){
            jouer(&statut, resultat);
            }

        if(statut == 'J'){
            game_pause(&statut, resultat, &compteur, &temps);
        }

        if(statut == 'P'){
            game_pause(&statut, resultat, &compteur, &temps);
        }
        
        if(resultat == 'Q' || resultat == 'q'){
            statut = 'Q';
            resultat=0;
        }
    }
    return 0;
}


char key_pressed()
{
    struct termios oldterm, newterm;
    int oldfd; char c, result = 0;
    
    tcgetattr (STDIN_FILENO, &oldterm);
    newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
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
















