#ifndef PLAYER_H
#define PLAYER_H

#include <utility>
#include "../include/constants.h"
#include <array>
struct Tile;

enum class Direction { Up, Down, Left, Right };

class Player
{
public:
    Player(const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE> &);
    std::pair<int, int> getCoord() const;
    bool tryMove(Direction dir);
    void setCarryingGold(bool);
    bool isCarryingGold() const;

private:
    std::pair<int, int> coord;
    bool carryingGold;
    bool isValidMove(int, int) const;
};

#endif