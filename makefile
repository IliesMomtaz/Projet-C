# Compilateur
CC = gcc
CFLAGS = -Wall -Wextra -g -IInclude

# Fichiers sources
SRC = main.c \
      src/afficher_map.c \
      src/jouer.c \
      src/menu.c \
      src/game_pause.c

# Fichiers objets
OBJ = $(SRC:.c=.o)

# Nom de l'exécutable
EXEC = parking

# Règle par défaut
all: $(EXEC)

# Edition de liens
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Compilation de main avec ses dépendances
main.o: main.c Include/afficher_map.h Include/jouer.h Include/menu.h Include/game_pause.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Compilation générique pour les fichiers src/
src/%.o: src/%.c Include/%.h
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ) main.o $(EXEC)
