CC = gcc
CFLAGS = -Wall -Werror -g -std=c99

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRC_FILES = $(SRC_DIR)/main.c \
						$(SRC_DIR)/game.c \
            $(SRC_DIR)/player.c \
            $(SRC_DIR)/map.c \
            $(SRC_DIR)/window.c \
            $(SRC_DIR)/renderer.c \
            $(SRC_DIR)/raycaster.c \
						$(SRC_DIR)/utils.c \
						$(SRC_DIR)/inputs.c \
						$(SRC_DIR)/stack.c \
						$(SRC_DIR)/linkedlist.c \
						$(SRC_DIR)/graph.c \
						$(SRC_DIR)/state.c \
						$(SRC_DIR)/types.c

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OUTPUT = raycast

#make an obj dir if it doesnt exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OUTPUT): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(OUTPUT) -lSDL2 -lSDL2_ttf -lm

clean:
	rm -f $(OBJ_DIR)/*.o $(OUTPUT)

rebuild: clean $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)

.PHONY: clean rebuild run

