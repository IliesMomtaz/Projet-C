# Compilateur
CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -IInclude

# Dossiers
SRC_DIR = src
INC_DIR = Include

# Executable
EXEC = parking

# Fichiers sources (avec les nouveaux fichiers de Personne 2)
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/menu.c \
      $(SRC_DIR)/jouer.c \
      $(SRC_DIR)/game_pause.c \
      $(SRC_DIR)/afficher_map.c \
      $(SRC_DIR)/map.c \
      $(SRC_DIR)/Voiture.c \
      $(SRC_DIR)/fonctions.c

# Fichiers objets
OBJ = $(SRC:.c=.o)

# Règle par défaut
all: $(EXEC)

# Link
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation des .c en .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(SRC_DIR)/*.o $(EXEC)