#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include <array>
#include <utility>
#include "Dungeon.h"
#include "Player.h"

struct Tile;

class GameWindow
{
public:
    GameWindow();
    void run(std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE> &);
    void drawGrid(const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE> &, const std::pair<int, int> &);

private:
    sf::RenderWindow window;
    std::string statusMessage;
    sf::Font font;
    sf::Font iconFont;
    sf::Text statusText;
    void updateWindow(const std::string &, const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE> &, const Player &);
    sf::Event waitForEvent(sf::RenderWindow &);
    void handleInput(sf::Event &, Player &);
};

#endif
