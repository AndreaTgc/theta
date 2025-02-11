# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -Wpedantic -fsanitize=address -std=c11 -DDEBUG_MODE 
LDFLAGS = -fsanitize=address 

# Directories
SRC_DIR = src
OBJ_DIR = bin/obj
BIN_DIR = bin

# Output executable
EXEC = $(BIN_DIR)/chess_engine

# Find all .c source files in src/
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Generate object file paths in obj/ from src/
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule
all: $(EXEC)

# Create the executable
$(EXEC): $(OBJS) | $(BIN_DIR)
	@$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Compile each .c file into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Ensure bin and obj directories exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Run the program
run: $(EXEC)
	@./$(EXEC)

# Clean up object files and the executable
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean run

