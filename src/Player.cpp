#include "Player.h"
#include "Dungeon.h"

Player::Player(const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE> &dungeon)
{
    coord = INIT_COORD;
    carryingGold = false;
}

std::pair<int, int> Player::getCoord() const
{
    return coord;
}

bool Player::isValidMove(int dr, int dc) const
{
    int newRow = coord.first + dr;
    int newCol = coord.second + dc;
    return (newRow >= 0 && newRow < DUNGEON_SIZE &&
            newCol >= 0 && newCol < DUNGEON_SIZE);
}

void Player::setCarryingGold(bool val)
{
    carryingGold = val;
}

bool Player::isCarryingGold() const
{
    return carryingGold;
}

bool Player::tryMove(Direction dir)
{
    int dr = 0, dc = 0;
    switch (dir)
    {
        case Direction::Up:    dr = -1; break;
        case Direction::Down:  dr = 1;  break;
        case Direction::Left:  dc = -1; break;
        case Direction::Right: dc = 1;  break;
    }

    if (isValidMove(dr, dc))
    {
        coord.first += dr;
        coord.second += dc;
        return true;
    }
    return false;
}