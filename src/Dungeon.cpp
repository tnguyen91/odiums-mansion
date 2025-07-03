#include "Dungeon.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int random(int min, int max)
{
    return min + rand() % ((max - min) + 1);
}

std::pair<int, int> getRandCoord()
{
    int r = rand() % DUNGEON_SIZE;
    int c = rand() % DUNGEON_SIZE;
    return std::make_pair(r, c);
}

void setUpDungeon(std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE> &dungeon)
{
    // Initialize empty
    for (int i = 0; i < DUNGEON_SIZE; ++i)
        for (int j = 0; j < DUNGEON_SIZE; ++j)
            dungeon[i][j] = Tile();

    // Set starting point
    dungeon[0][0].setStartingPoint(true);
    dungeon[0][0].reveal();

    // Place evil
    std::pair<int, int> evilCoord;
    while (true)
    {
        evilCoord = getRandCoord();
        if (dungeon[evilCoord.first][evilCoord.second].isEmpty() &&
            !(evilCoord.first == 1 && evilCoord.second == 0) &&
            !(evilCoord.first == 0 && evilCoord.second == 1))
        {
            dungeon[evilCoord.first][evilCoord.second].setEvil(true);
            break;
        }
    }

    // Add stench around
    for (int dr = -1; dr <= 1; ++dr)
    {
        for (int dc = -1; dc <= 1; ++dc)
        {
            if (abs(dr) + abs(dc) == 1)
            {
                int nr = evilCoord.first + dr, nc = evilCoord.second + dc;
                if (nr >= 0 && nr < DUNGEON_SIZE && nc >= 0 && nc < DUNGEON_SIZE)
                {
                    dungeon[nr][nc].setStench(true);
                }
            }
        }
    }

    // Place pits
    for (int i = 0; i < NUM_PITS; ++i)
    {
        std::pair<int, int> pitCoord;
        while (true)
        {
            pitCoord = getRandCoord();
            if (dungeon[pitCoord.first][pitCoord.second].isEmpty() &&
                !(pitCoord.first == 1 && pitCoord.second == 0) &&
                !(pitCoord.first == 0 && pitCoord.second == 1))
            {
                dungeon[pitCoord.first][pitCoord.second].setPit(true);
                break;
            }
        }
        // Add breezes around
        for (int dr = -1; dr <= 1; ++dr)
        {
            for (int dc = -1; dc <= 1; ++dc)
            {
                if (abs(dr) + abs(dc) == 1)
                {
                    int nr = pitCoord.first + dr, nc = pitCoord.second + dc;
                    if (nr >= 0 && nr < DUNGEON_SIZE && nc >= 0 && nc < DUNGEON_SIZE)
                    {
                        dungeon[nr][nc].setBreeze(true);
                    }
                }
            }
        }
    }

    // Place gold
    std::pair<int, int> goldCoord;
    while (true)
    {
        goldCoord = getRandCoord();
        if (dungeon[goldCoord.first][goldCoord.second].isEmpty() &&
            !(goldCoord.first == 1 && goldCoord.second == 0) &&
            !(goldCoord.first == 0 && goldCoord.second == 1))
        {
            dungeon[goldCoord.first][goldCoord.second].setGold(true);
            break;
        }
    }
}

void printDungeon(const std::array<std::array<char, DUNGEON_SIZE>, DUNGEON_SIZE> &dungeon, const std::pair<int, int> &playerPos, bool revealAll)
{
    std::cout << "\nDungeon Map:" << std::endl;
    for (int i = 0; i < DUNGEON_SIZE; ++i)
    {
        for (int j = 0; j < DUNGEON_SIZE; ++j)
        {
            if (playerPos.first == i && playerPos.second == j)
            {
                std::cout << " P ";
            }
            else if (revealAll)
            {
                std::cout << " " << dungeon[i][j] << " ";
            }
            else
            {
                std::cout << " . ";
            }
        }
        std::cout << std::endl;
    }
}