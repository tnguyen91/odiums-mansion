#ifndef DUNGEON_H
#define DUNGEON_H

#include <array>
#include <utility>
#include "../include/constants.h"
#include "GameWindow.h"

class Tile {
public:
    Tile() = default;

    // Queries
    bool isEmpty() const {
        return !m_hasPit && !m_hasGold && !m_hasEvil && !m_hasBreeze && !m_hasStench && !revealed;
    }

    bool hasHazard() const {
        return m_hasPit || m_hasEvil;
    }

    bool hasWarning() const {
        return m_hasBreeze || m_hasStench;
    }

    bool isSafe() const {
        return !hasHazard();
    }

    bool isRevealed() const { return revealed; }
    void reveal() { revealed = true; }
    bool isStartingPoint() const { return startingPoint; }
    void setStartingPoint(bool val) { startingPoint = val; }
    bool hasPit() const { return m_hasPit; }
    void setPit(bool val) { m_hasPit = val; }
    bool hasGold() const { return m_hasGold; }
    void setGold(bool val) { m_hasGold = val; }
    bool hasEvil() const { return m_hasEvil; }
    void setEvil(bool val) { m_hasEvil = val; }
    bool hasBreeze() const { return m_hasBreeze; }
    void setBreeze(bool val) { m_hasBreeze = val; }
    bool hasStench() const { return m_hasStench; }
    void setStench(bool val) { m_hasStench = val; }

private:
    bool revealed = false;
    bool startingPoint = false;
    bool m_hasPit = false;
    bool m_hasGold = false;
    bool m_hasEvil = false;
    bool m_hasBreeze = false;
    bool m_hasStench = false;
};

int random(int, int);
std::pair<int, int> getRandCoord();
void setUpDungeon(std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE> &);
void printDungeon(const std::array<std::array<char, DUNGEON_SIZE>, DUNGEON_SIZE> &, const std::pair<int, int> &, bool);

#endif
