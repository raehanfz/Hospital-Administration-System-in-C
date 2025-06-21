# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN = main

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_FILES += main.c

OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))

# Default target
all: $(BIN)

# Link object files into the binary
$(BIN): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@

# Generic rule for object files from src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Special rule for main.c
$(OBJ_DIR)/main.o: main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean
