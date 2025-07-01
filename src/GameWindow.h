#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include <array>
#include <utility>
#include "constants.h"

struct Tile;

class GameWindow {
public:
    GameWindow();
    void run(std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon);
    void drawGrid(const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon, const std::pair<int, int>& playerPos);

private:
    sf::RenderWindow window;
};

#endif