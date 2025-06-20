# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN = testing

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c) testing.c
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

# Default target
all: $(BIN)

# Link object files into the final binary
$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compile each source file into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/testing.o: testing.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean
