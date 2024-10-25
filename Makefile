# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS = 

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
TEST_DIR = test
OBJ_DIR = obj

# Files
EXEC = $(BIN_DIR)/dennis
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Targets
.PHONY: all clean test run

# Default target
all: $(EXEC)

# Build executable
$(EXEC): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ $(LDFLAGS)
	@echo "Executable created: $(EXEC)"

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled: $<"

# Create necessary directories
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Run the executable
run: $(EXEC)
	@echo "Running $(EXEC)..."
	./$(EXEC)

# Testing target (if you have test files)
test: $(EXEC)
	@echo "Running tests..."
	# Add your test commands here, e.g., $(TEST_DIR)/test_program
	@echo "Tests completed."

# Clean the build
clean:
	@echo "Cleaning project..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaned."

