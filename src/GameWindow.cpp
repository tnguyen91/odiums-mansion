#include "GameWindow.h"
#include "Player.h"
#include <iostream>
#include "Dungeon.h"

GameWindow::GameWindow() : window(sf::VideoMode(640, 640), "Odium's Mansion") {}

void GameWindow::run(std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon) {
    Player player(dungeon);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                switch (event.key.code) {
                    case sf::Keyboard::W: player.move(-1, 0); break;
                    case sf::Keyboard::S: player.move(1, 0); break;
                    case sf::Keyboard::A: player.move(0, -1); break;
                    case sf::Keyboard::D: player.move(0, 1); break;
                    default: break;
                }
            } 
        }
        std::pair<int, int> pos = player.getCoord();
        dungeon[pos.first][pos.second].isRevealed = true;
        drawGrid(dungeon, pos);
        Tile current = dungeon[pos.first][pos.second];

        if (current.hasPit) {
            std::cout << "You fell into a pit! Game Over.\n";
            sf::sleep(sf::seconds(2));
            window.close();
        } else if (current.hasEvil) {
            std::cout << "You encountered evil! Game Over.\n";
            sf::sleep(sf::seconds(2));
            window.close();
        } else if (current.hasGold) {
            std::cout << "You found the gold! Now return to (0,0) to escape.\n";
            current.hasGold = false;
            player.setCarryingGold(true);
            dungeon[pos.first][pos.second] = current;
        } else if (player.isCarryingGold() && player.getCoord() == std::make_pair(0, 0)) {
            std::cout << "You escaped with the gold! You win!\n";
            sf::sleep(sf::seconds(2));
            window.close();
        }

    }
}

void GameWindow::drawGrid(const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon, const std::pair<int, int>& playerPos) {
    window.clear();

    const float tileSize = 640.0f / DUNGEON_SIZE;

    for (int i = 0; i < DUNGEON_SIZE; ++i) {
        for (int j = 0; j < DUNGEON_SIZE; ++j) {
            sf::RectangleShape cell(sf::Vector2f(tileSize, tileSize));
            cell.setPosition(j * tileSize, i * tileSize);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);

            const Tile& t = dungeon[i][j];

            if (t.isRevealed) {
                if (i == playerPos.first && j == playerPos.second) 
                    cell.setFillColor(sf::Color::Green); // Player position
                else if (t.hasPit) cell.setFillColor(sf::Color::Black);
                else if (t.hasEvil) cell.setFillColor(sf::Color::Red);
                else if (t.hasGold) cell.setFillColor(sf::Color::Yellow);
                else if (t.hasStench) cell.setFillColor(sf::Color(128, 0, 128)); // Purple for stench
                else if (t.hasBreeze) cell.setFillColor(sf::Color::Cyan);
                else cell.setFillColor(sf::Color::White);
            } else {
                cell.setFillColor(sf::Color(169, 169, 169)); // Dark gray for unrevealed
            }
            window.draw(cell);
        }
    }

    window.display();
}