CC = gcc
CFLAGS = -Wall -Wextra -O2
BIN_DIR = bin
OBJ_DIR = build
TARGET = ej9

SRC = ej9.c
OBJ = $(OBJ_DIR)/ej9.o

$(BIN_DIR)/$(TARGET): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
