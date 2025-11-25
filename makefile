SRC_DIR := src
INC_DIR := Include

CC      := gcc
CFLAGS  := -Wall -Wextra -g -I$(INC_DIR)

SRC := main.c \
       $(SRC_DIR)/afficher_map.c \
       $(SRC_DIR)/jouer.c \
       $(SRC_DIR)/menu.c \
       $(SRC_DIR)/game_pause.c \
       $(SRC_DIR)/map.c

OBJ  := $(SRC:.c=.o)
EXEC := parking

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

re: clean all

run: $(EXEC)
	./$(EXEC)
