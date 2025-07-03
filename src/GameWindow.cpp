#include "GameWindow.h"
#include "Player.h"
#include <iostream>
#include "Dungeon.h"

GameWindow::GameWindow() : window(sf::VideoMode(640, 640 + 80), "Odium's Mansion") {
	if (!font.loadFromFile("assets/CinzelDecorative-Regular.ttf")) {
		std::cerr << "Failed to load font!\n";
	}

	statusText.setFont(font);
    statusText.setCharacterSize(20);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(10.f, 770.f);
}

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
        Tile current = dungeon[pos.first][pos.second];

		if (current.hasBreeze && current.hasStench){
			updateWindow("You feel a breeze and smell a stench...", dungeon, pos);
		}
		else if (current.hasBreeze){
            updateWindow("You feel a breeze...", dungeon, pos);
		}
		else if (current.hasStench){
			updateWindow("You smell a stench...", dungeon, pos);
		}
		else if (current.hasPit) {
            updateWindow("You fell into a pit! Game Over.", dungeon, pos);
            sf::sleep(sf::seconds(2));
            //window.close();
        } else if (current.hasEvil) {
            updateWindow("You encountered an evil creature! Game Over.", dungeon, pos);
            sf::sleep(sf::seconds(2));
            //window.close();
        } else if (current.hasGold) {
            updateWindow("You found the gold! Return to (0, 0) to escape.", dungeon, pos);
            current.hasGold = false;
            player.setCarryingGold(true);
            dungeon[pos.first][pos.second] = current;
        } else if (player.isCarryingGold() && player.getCoord() == std::make_pair(0, 0)) {
            updateWindow("You escaped with the gold! You win!", dungeon, pos);
            sf::sleep(sf::seconds(2));
            //window.close();
        }
        else {
            updateWindow("You are in a safe area.", dungeon, pos);
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
	const float messageHeight = 24.f;
    sf::RectangleShape messageBar(sf::Vector2f(window.getSize().x, messageHeight));
    messageBar.setFillColor(sf::Color::Transparent);
    messageBar.setPosition(0, DUNGEON_SIZE * tileSize);
    window.draw(messageBar);

    // Status text
	statusText.setFont(font);
    statusText.setCharacterSize(18);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(10.f, DUNGEON_SIZE * tileSize + 4.f);
    window.draw(statusText);

    window.display();
}

void GameWindow::updateWindow(const std::string& message, const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon, const std::pair<int, int>& pos) {
	statusMessage = message;
	statusText.setString(statusMessage);
    drawGrid(dungeon, pos);
}
