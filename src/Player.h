#ifndef PLAYER_H
#define PLAYER_H

#include <utility>
#include "../include/constants.h"
#include <array>
struct Tile;

class Player {
public:
    Player(const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon);
    std::pair<int, int> getCoord() const;
    void move(int dr, int dc);
    bool isValidMove(int dr, int dc) const;

private:
    std::pair<int, int> coord;
};

#endif