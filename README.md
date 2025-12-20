
## Simulateur de Parking - Langage C


Ce jeu est une simulation de stationnement de voitures dans un parking payant, développé en langage C. Il tient compte des déplacement et du stationnement des véhicules sur une map graphique basée sur les séquences ANSI.


Fonctionnalités :

Menu interactif

Affichage du parking en mode texte (ASCII et ANSI)

Déplacement manuel des véhicules

Gestion des places libres / occupées

Détection simple des collisions (murs, autres véhicules, etc.)

Mise à jour du parking en temps réel

Sortie automatique des voitures du parking (géré avec l'IA)


Le projet est organisé de la manière suivante :

- src : Contient les fichiers sources .c du projet (main.c, menu.c, afficher_map.c, Vehicule.c) et les fichiers intermédiaires (en .o) générés lors de la compilation
- include : Contient les fichiers d'en tête (en .h)  
- sprite : Contient les fichiers .txt de la map et des véhicules



## Prérequis

Pour jouer à ce jeu, il vous faut :

- Un système d'exploitation Linux et un terminal
- Le compilateur gcc


## Installation et Compilation


Ouvrez un terminal à la racine du projet et faites la commande suivante :
```
make (gérée par le fichier Makefile)
```


## Utilisation

1) Lancement

Une fois compilé, lancez le jeu avec :

```
./parking
```

2) Contrôles

- Choisissez le mode de jeu depuis le menu :

   1) Mode fluide, la voiture reste moins longtemps dans le parking

   2) Mode Chargé : la voiture reste plus longtemps dans le parking

- Touches pour déplacer les véhicules : A (haut), B (bas), C (droite), D (gauche)

- Appuyez sur espace pour se garer et arreter le véhicule

- Appuyez sur Q ou X pour quitter


## FIN
