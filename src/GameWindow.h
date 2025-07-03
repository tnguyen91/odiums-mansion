#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include <array>
#include <utility>
#include "constants.h"
#include "Dungeon.h"
#include "Player.h"

struct Tile;

class GameWindow {
public:
    GameWindow();
    void run(std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon);
    void drawGrid(const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon, const std::pair<int, int>& playerPos);

private:
    sf::RenderWindow window;
	std::string statusMessage;
    sf::Font font;
	sf::Font iconFont;
    sf::Text statusText;
	void updateWindow(const std::string&, const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon, const std::pair<int, int>& pos);
    sf::Event waitForEvent(sf::RenderWindow& window);
    void handleInput(sf::Event& event, Player& player);
};

#endif
