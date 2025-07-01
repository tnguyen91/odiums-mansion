#include "Dungeon.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int random(int min, int max) {
    return min + rand() % ((max - min) + 1);
}

std::pair<int, int> getDungeonCoord() {
    int r = rand() % DUNGEON_SIZE;
    int c = rand() % DUNGEON_SIZE;
    return {r, c};
}

void setUpDungeon(std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon) {
    // Initialize empty
    for (int i = 0; i < DUNGEON_SIZE; ++i)
        for (int j = 0; j < DUNGEON_SIZE; ++j)
            dungeon[i][j] = Tile();

    // Place pits
    for (int i = 0; i < 8; ++i) {
        auto [r, c] = getDungeonCoord();
        dungeon[r][c].hasPit = true;

        // Add breezes around
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (abs(dr) + abs(dc) == 1) {
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < DUNGEON_SIZE && nc >= 0 && nc < DUNGEON_SIZE) {
                        dungeon[nr][nc].hasBreeze = true;
                    }
                }
            }
        }
    }

    // Place gold
    auto [gr, gc] = getDungeonCoord();
    dungeon[gr][gc].hasGold = true;

    // Place evil
    auto [er, ec] = getDungeonCoord();
    dungeon[er][ec].hasEnemy = true;

    // Add stench around
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (abs(dr) + abs(dc) == 1) {
                int nr = er + dr, nc = ec + dc;
                if (nr >= 0 && nr < DUNGEON_SIZE && nc >= 0 && nc < DUNGEON_SIZE) {
                    dungeon[nr][nc].hasStench = true;
                }
            }
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
