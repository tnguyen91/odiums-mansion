#include "Player.h"
#include "Dungeon.h"

Player::Player(const std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon) {
    for (int i = 0; i < DUNGEON_SIZE; ++i) {
        for (int j = 0; j < DUNGEON_SIZE; ++j) {
            if (!dungeon[i][j].hasPit && !dungeon[i][j].hasEvil) {
                coord = {i, j};
                return;
            }
        }
    }
}

std::pair<int, int> Player::getCoord() const {
    return coord;
}

void Player::move(int dr, int dc) {
    int newRow = coord.first + dr;
    int newCol = coord.second + dc;
    if (isValidMove(dr, dc)) {
        coord.first = newRow;
        coord.second = newCol;
    }
}

bool Player::isValidMove(int dr, int dc) const {
    int newRow = coord.first + dr;
    int newCol = coord.second + dc;
    return (newRow >= 0 && newRow < DUNGEON_SIZE &&
            newCol >= 0 && newCol < DUNGEON_SIZE);
}

void Player::setCarryingGold(bool val) {
    carryingGold = val;
}

bool Player::isCarryingGold() const {
    return carryingGold;
}