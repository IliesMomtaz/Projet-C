#include <stdio.h>
#include <unistd.h> 
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include "menu.h"

char key_pressed();

int main()
{
    menu();
    char statut = 'M'; // on va avoir trois états : M(Menu), J(Jouer), P(Pause) et Q(Quit)

    while(statut != 'Q'){
        char resultat = key_pressed();

        if(resultat == 'M' || resultat == 'm'){ // Si pendant le jeu le joueur veut retourner dans le menu, en le remettant ici il le peut
            statut = 'M';
            menu();
            resultat = 0; // je remet a chaque fois a 0 pcq sinon pour le pause/play ca posait probleme
        }

        if(statut == 'M'){
            if(resultat == '1' || resultat == '2'){
                statut = 'J';
                printf("Le Jeu à commencer !!\n");
                if(resultat == '1'){
                    //activer le mode Fluide 
                    printf("\033[2J\033[H");
                    FILE *f = fopen("map.txt", "r");
                    char ligne[256];
                    while (fgets(ligne, sizeof(ligne), f) != NULL){
                        printf("%s", ligne);
                    }
                    fclose(f);
                    resultat=0;
                }
            if(resultat == '2'){
                //activer le mode Charger
                printf("\033[2J\033[H"); // pour nettoyer l'écran
                FILE *f = fopen("assets-voiture.txt", "r");
                    char ligne[256];
                    while (fgets(ligne, sizeof(ligne), f) != NULL){
                        printf("%s", ligne);
                    }
                    printf("\n");
                    fclose(f);
                resultat=0;
            }
        }
        }

        if(statut == 'J'){
            if(resultat == 'P' || resultat == 'p'){
                statut = 'P';
                printf("==========LE JEU EST EN PAUSE==========\n");
                resultat=0;
            }
        }

        if(statut == 'P'){
            if(resultat == 'P' || resultat == 'p'){
                statut = 'J';
                printf("=============LE JEU REPREND============\n");
                resultat=0;
            }
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





// Trucs à corriger : quand on la ce le programme et qu'on appui sur 1 par exemple, le chiffre apparait quand le message "Le jeu..." arrive
// à voir si ca le refait quand y'aura la vraie interface
// quand on appui sur q pour quitter juste enlever le pourcentage