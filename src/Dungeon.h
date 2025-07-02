#ifndef DUNGEON_H
#define DUNGEON_H

#include <array>
#include <utility>
#include "../include/constants.h"
#include "GameWindow.h"

struct Tile {
    bool hasPit = false;
    bool hasGold = false;
    bool hasEvil= false;
    bool hasBreeze = false;
    bool hasStench = false;
    bool isRevealed = false;
};

int random(int, int);
void printDungeon(const std::array<std::array<char, DUNGEON_SIZE>, DUNGEON_SIZE>&, const std::pair<int, int>&, bool);
void setUpDungeon(std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon);
std::pair<int, int> getRandCoord();
bool isEmptyTile(std::pair<int, int> coord, const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon);
#endif
