#include "Dungeon.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int random(int min, int max) {
    return min + rand() % ((max - min) + 1);
}

std::pair<int, int> getRandCoord() {
    int r = rand() % DUNGEON_SIZE;
    int c = rand() % DUNGEON_SIZE;
    return std::make_pair(r, c);
}

void setUpDungeon(std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon) {
    // Initialize empty
    for (int i = 0; i < DUNGEON_SIZE; ++i)
        for (int j = 0; j < DUNGEON_SIZE; ++j)
            dungeon[i][j] = Tile();

    // Set starting point
    dungeon[0][0].startingPoint = true;
    dungeon[0][0].isRevealed = true;

    // Place evil
    std::pair<int, int> evilCoord;
    while (true) {
        evilCoord = getRandCoord();
        if (isEmptyTile(evilCoord, dungeon)){
            dungeon[evilCoord.first][evilCoord.second].hasEvil = true;
            break;
        }
    }

    // Add stench around
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (abs(dr) + abs(dc) == 1) {
                int nr = evilCoord.first + dr, nc = evilCoord.second + dc;
                if (nr >= 0 && nr < DUNGEON_SIZE && nc >= 0 && nc < DUNGEON_SIZE) {
                    dungeon[nr][nc].hasStench = true;
                }
            }
        }
    }

    // Place pits
    for (int i = 0; i < 8; ++i) {
        std::pair<int, int> pitCoord;
        while (true) {
            pitCoord = getRandCoord();
            if (isEmptyTile(pitCoord, dungeon)){
                dungeon[pitCoord.first][pitCoord.second].hasPit = true;
                break;
            }
        }
        // Add breezes around
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (abs(dr) + abs(dc) == 1) {
                    int nr = pitCoord.first + dr, nc = pitCoord.second + dc;
                    if (nr >= 0 && nr < DUNGEON_SIZE && nc >= 0 && nc < DUNGEON_SIZE) {
                        dungeon[nr][nc].hasBreeze = true;
                    }
                }
            }
        }
    }

    // Place gold
    std::pair<int, int> goldCoord;
    while (true) {
        goldCoord = getRandCoord();
        if (isEmptyTile(goldCoord, dungeon)){
            dungeon[goldCoord.first][goldCoord.second].hasGold = true;
            break;
        }
    }
}

void printDungeon(const std::array<std::array<char, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon, const std::pair<int, int>& playerPos, bool revealAll) {
    std::cout << "\nDungeon Map:" << std::endl;
    for (int i = 0; i < DUNGEON_SIZE; ++i) {
        for (int j = 0; j < DUNGEON_SIZE; ++j) {
            if (playerPos.first == i && playerPos.second == j) {
                std::cout << " P ";
            } else if (revealAll) {
                std::cout << " " << dungeon[i][j] << " ";
            } else {
                std::cout << " . ";
            }
        }
        std::cout << std::endl;
    }
}

bool isEmptyTile(std::pair<int, int> coord, const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon) {
    return  !dungeon[coord.first][coord.second].startingPoint &&
            !dungeon[coord.first][coord.second].hasStench && 
            !dungeon[coord.first][coord.second].hasBreeze &&
            !dungeon[coord.first][coord.second].hasPit && 
            !dungeon[coord.first][coord.second].hasEvil && 
            !dungeon[coord.first][coord.second].hasGold &&
            !(coord.first == 1 && coord.second == 0) &&
            !(coord.first == 0 && coord.second == 1);
}