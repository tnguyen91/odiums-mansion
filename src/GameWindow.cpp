#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow() : window(sf::VideoMode(640, 640 + 80), "Odium's Mansion")
{
    if (!font.loadFromFile("assets/CinzelDecorative-Regular.ttf"))
    {
        std::cerr << "Failed to load font!\n";
    }

    if (!iconFont.loadFromFile("assets/FontAwesome6Free-Solid-900.otf"))
    {
        std::cerr << "Failed to load emoji font!\n";
    }

    statusText.setFont(font);
    statusText.setCharacterSize(20);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(10.f, 770.f);
}

void GameWindow::run(std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE> &dungeon)
{
    Player player(dungeon);
    updateWindow("Welcome to Odium's Mansion!\nUse W/A/S/D to move.\nFind the gold and escape!", dungeon, player);
    while (window.isOpen())
    {
        sf::Event event;
        event = waitForEvent(window);
        handleInput(event, player);
        std::pair<int, int> pos = player.getCoord();
        dungeon[pos.first][pos.second].reveal();
        Tile current = dungeon[pos.first][pos.second];

        if (player.isCarryingGold() && player.getCoord() == std::make_pair(0, 0))
        {
            updateWindow("You escaped with the gold!\nYou win!", dungeon, player);
            sf::sleep(sf::seconds(2));
            window.close();
        }
        else if (current.hasPit())
        {
            updateWindow("You fell into a pit! Game Over.", dungeon, player);
            sf::sleep(sf::seconds(2));
            window.close();
        }
        else if (current.hasEvil())
        {
            updateWindow("You encountered an evil creature!\nGame Over.", dungeon, player);
            sf::sleep(sf::seconds(2));
            window.close();
        }
        else if (current.hasGold())
        {
            updateWindow("You found the gold! \nReturn to the starting point to escape.", dungeon, player);
            player.setCarryingGold(true);
            dungeon[pos.first][pos.second].setGold(false); // Remove gold from the tile
        }
        else if (current.hasBreeze() && current.hasStench())
        {
            updateWindow("You feel a breeze and smell a stench...", dungeon, player);
        }
        else if (current.hasBreeze())
        {
            updateWindow("You feel a breeze...", dungeon, player);
        }
        else if (current.hasStench())
        {
            updateWindow("You smell a stench...", dungeon, player);
        }
        else
        {
            updateWindow("You are in a safe area.", dungeon, player);
        }
    }
}

void GameWindow::drawGrid(const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE> &dungeon, const std::pair<int, int> &playerPos)
{
    window.clear();

    const float tileSize = 640.0f / DUNGEON_SIZE;

    for (int i = 0; i < DUNGEON_SIZE; ++i)
    {
        for (int j = 0; j < DUNGEON_SIZE; ++j)
        {
            sf::RectangleShape cell(sf::Vector2f(tileSize, tileSize));
            cell.setPosition(j * tileSize, i * tileSize);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);

            const Tile &t = dungeon[i][j];

            if (t.isRevealed())
            {
                cell.setFillColor(sf::Color::White);
            }
            else
            {
                cell.setFillColor(sf::Color(169, 169, 169)); // Dark gray for unrevealed
            }
            window.draw(cell);

            if (t.isRevealed())
            {
                sf::Text iconText;
                iconText.setFont(iconFont);
                iconText.setCharacterSize(tileSize / 3);
                iconText.setFillColor(sf::Color::Black);

                auto setIcon = [&](const std::vector<sf::String> &icons, bool topHalf = false)
                {
                    std::vector<sf::Text> texts;
                    float spacing = 4.f;
                    float totalWidth = 0.f;

                    // Create texts and compute total width
                    for (const auto &icon : icons)
                    {
                        iconText.setString(icon);
                        sf::FloatRect bounds = iconText.getLocalBounds();
                        sf::Text text(icon, iconFont, iconText.getCharacterSize());
                        text.setFillColor(iconText.getFillColor());
                        texts.push_back(text);
                        totalWidth += bounds.width;
                    }

                    totalWidth += spacing * (texts.size() - 1);

                    float centerX = j * tileSize + tileSize / 2.f;
                    float centerY = i * tileSize + (topHalf ? tileSize / 4.f : 3 * tileSize / 4.f);
                    float startX = centerX - totalWidth / 2.f;

                    // Draw all icons centered
                    for (auto &text : texts)
                    {
                        sf::FloatRect bounds = text.getLocalBounds();
                        text.setOrigin(bounds.left, bounds.top + bounds.height / 2.f); // vertical center
                        text.setPosition(startX, centerY);
                        window.draw(text);
                        startX += bounds.width + spacing;
                    }
                };

                if (i == playerPos.first && j == playerPos.second)
                {
                    setIcon({L"\uf007"}, true); // true = top half
                }

                // Status icons in bottom half
                std::vector<sf::String> icons;
                if (t.isStartingPoint())
                    icons.push_back(L"\uf024");
                if (t.hasBreeze())
                    icons.push_back(L"\uf72e");
                if (t.hasStench())
                    icons.push_back(L"\uf071");
                if (t.hasPit())
                    icons.push_back(L"\ue546");
                if (t.hasEvil())
                    icons.push_back(L"\uf714");
                if (t.hasGold())
                    icons.push_back(L"\uf3a5");

                if (!icons.empty())
                {
                    setIcon(icons);
                }
            }
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

void GameWindow::updateWindow(const std::string &message, const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE> &dungeon, const Player &player)
{
    std::pair<int, int> pos = player.getCoord();
    if (player.isCarryingGold())
    {
        std::string goldMessage = "You are carrying the gold!";
        statusMessage = goldMessage + '\n' + message;
    }
    else
    {
        statusMessage = message;
    }
    window.clear();
    statusText.setString(statusMessage);
    drawGrid(dungeon, pos);
}

sf::Event GameWindow::waitForEvent(sf::RenderWindow &window)
{
    sf::Event event;
    while (true)
    {
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed && event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                return event;
            }
        }
    }
}

void GameWindow::handleInput(sf::Event &event, Player &player)
{
    switch (event.key.code)
    {
    case sf::Keyboard::W:
        player.tryMove(Direction::Up);
        break;
    case sf::Keyboard::S:
        player.tryMove(Direction::Down);
        break;
    case sf::Keyboard::A:
        player.tryMove(Direction::Left);
        break;
    case sf::Keyboard::D:
        player.tryMove(Direction::Right);
        break;
    default:
        break;
    }
}