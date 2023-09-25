CXX = g++

OBJ = ./obj
BIN = ./bin
INC = ./inc
SRC = ./src

CXXFLAGS = -std=c++20 -I $(INC) -I /opt/local/include
LDFLAGS = -L /opt/local/lib -lraylib -lm -lpthread -lX11

all: dirs run

run: $(BIN)/main	
	$(BIN)/main

# driver
$(BIN)/main: $(OBJ)/main.o
	$(CXX) $(LDFLAGS) $(OBJ)/main.o -o $(BIN)/main

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

dirs:
	mkdir -p $(BIN)
	mkdir -p $(OBJ)

clean:
	rm -rf $(BIN) $(OBJ)