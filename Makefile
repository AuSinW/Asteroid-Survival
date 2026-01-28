# Compiler
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude -I../Engine/include
LDFLAGS = -L../Engine -lClinetGFX -lgdi32 -mwindows

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Executable
TARGET = $(BIN_DIR)/asteroids.exe

# Sources and objects
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR)
	@if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)

