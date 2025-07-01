CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = src/main.cpp src/Dungeon.cpp src/Player.cpp src/GameWindow.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = odiums_mansion

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)