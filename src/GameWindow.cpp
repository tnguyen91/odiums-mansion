#include "GameWindow.h"
#include "Player.h"
#include <iostream>
#include "Dungeon.h"

GameWindow::GameWindow() : window(sf::VideoMode(640, 640), "Odium's Mansion - SFML") {}

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
        drawGrid(dungeon, player.getCoord());
        auto [r, c] = player.getCoord();
        Tile current = dungeon[r][c];

        if (current.hasPit) {
            std::cout << "You fell into a pit! Game Over.\n";
            sf::sleep(sf::seconds(2));
            window.close();
        } else if (current.hasEnemy) {
            std::cout << "You encountered evil! Game Over.\n";
            sf::sleep(sf::seconds(2));
            window.close();
        } else if (current.hasGold) {
            std::cout << "You found the gold! You win!\n";
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

            if (playerPos.first == i && playerPos.second == j) {
                cell.setFillColor(sf::Color::Green);
            } else if (t.hasEnemy) {
                cell.setFillColor(sf::Color::Red);
            } else if (t.hasGold) {
                cell.setFillColor(sf::Color::Yellow);
            } else if (t.hasPit) {
                cell.setFillColor(sf::Color(139, 69, 19));  // Brown
            } else if (t.hasStench && t.hasBreeze) {
                cell.setFillColor(sf::Color(186, 85, 211)); // Violet
            } else if (t.hasStench) {
                cell.setFillColor(sf::Color::Magenta);
            } else if (t.hasBreeze) {
                cell.setFillColor(sf::Color::Cyan);
            } else {
                cell.setFillColor(sf::Color(80, 80, 80)); // Empty tile
            }

            window.draw(cell);
        }
    }

    window.display();
}