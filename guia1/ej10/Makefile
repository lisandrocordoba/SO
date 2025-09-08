CC = gcc
CFLAGS = -Wall -Wextra -O2
BIN_DIR = bin
OBJ_DIR = build
TARGET = ej10

SRC = ej10.c
OBJ = $(OBJ_DIR)/ej10.o

$(BIN_DIR)/$(TARGET): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
