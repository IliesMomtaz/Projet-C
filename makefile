# Compilateur
CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -IInclude

# Dossiers
SRC_DIR = src

# Executable
EXEC = parking

# Fichiers sources
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/menu.c \
      $(SRC_DIR)/jouer.c \
      $(SRC_DIR)/game_pause.c \
      $(SRC_DIR)/afficher_map.c \
      $(SRC_DIR)/map.c

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

.PHONY: all clean
