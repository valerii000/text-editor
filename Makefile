# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23
LDFLAGS = 

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = build
TEST_DIR = tests

# Source files and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TEST_FILES = $(wildcard $(TEST_DIR)/*)

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
	@result=''; \
	for TEST_FILE in $(TEST_FILES); do \
		result+=$$(echo "[$$TEST_FILE]\n"); \
		result+=$$($(TARGET) < $$TEST_FILE); \
		result+='\n\n'; \
	done; \
	echo -e $$result

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

cleant:
	@rm -rf $(TEST_DIR)/*

# Phony targets
.PHONY: build clean
