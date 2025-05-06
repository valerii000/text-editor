# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
LDFLAGS = -lncurses

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests
RES_DIR = results

# Source files and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TEST_FILES = $(wildcard $(TEST_DIR)/*)

DATE = $(shell date "+%d-%m-%Y_%H:%M:%S")

# Executable name
TARGET = $(BIN_DIR)/bin

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(LDFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	@rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Build target
build: $(TARGET)

# Run target
run:
	@$(TARGET)

# Test target
test:
	@mkdir -p $(RES_DIR); \
	RES_FILE=$(RES_DIR)/$(DATE); \
	touch $$RES_FILE; \
	for TEST_FILE in $(TEST_FILES); do \
		echo "[$$TEST_FILE]" >> $$RES_FILE; \
		$(TARGET) < $$TEST_FILE >> $$RES_FILE; \
		echo "" >> $$RES_FILE; \
		echo "" >> $$RES_FILE; \
	done; \
	cat $$RES_FILE;

testlist:
	@for TEST_FILE in $(TEST_FILES); do \
		echo "[$$TEST_FILE]"; \
		cat $$TEST_FILE; \
		echo ""; \
	done

addtest:
	@read -p "Enter test name: " name; \
	echo "Enter test content (^D for exit):"; \
	cat > $(TEST_DIR)/$$name

# Result target
result:
	@cat $(RES_DIR)/*;

# Clean results target
cleanr:
	@rm -rf $(RES_DIR)/*

cleant:
	@rm -rf $(TEST_DIR)/*

# Phony targets
.PHONY: all clean
