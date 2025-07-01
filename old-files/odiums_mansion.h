// who: <your name and Mt SAC username goes here>
// what: <the function of this program>
// why: <the name of the lab>
// when: <the due date of this lab.>
#include <string>
#include <array>

#ifndef ODIUMS_MANSION_H
#define  ODIUMS_MANSION_H

// If you are on a Microsoft Windows PC, set this to true
//  otherwise, leave it as false
#define WINDOWS true

#define START_VAL 0
#define END_VAL 7
#define DUNGEON_SIZE 8
#define QTY 14 // 12 pits, 1 evil, 1 gold
#define INIT_COORD 0, 0
#define STENCH 'S'
#define BREEZE 'B'
#define GLIMMER 'G'

class Player{
private:
    std::pair<int,int> playersCoord;
    std::array<std::array<std::string, DUNGEON_SIZE>, DUNGEON_SIZE> log;

    bool isValidMove(const char, bool&);
    void recordSensation(const char);
    std::string getCeil(const int, const int, const bool, const bool);
    
public:
    Player();
    std::pair<int, int> getCoord();
    void validMove(bool&);
    void sense(const std::array<std::array<char, DUNGEON_SIZE>, DUNGEON_SIZE>&);
    void printGrid(const bool);
};

void clearScreen();
void clearInstream();

void play(const std::array<std::array<char, DUNGEON_SIZE>, DUNGEON_SIZE>&);
bool notWin(const std::pair<int, int>&, const bool);
bool notLose(const std::pair<int, int>&, const std::array<std::array<char, DUNGEON_SIZE>, DUNGEON_SIZE>&);
std::array<std::pair<int, int>, QTY> getDungeonCoord();
void setUpDungeon(std::array<std::array<char, DUNGEON_SIZE>, DUNGEON_SIZE>&, const std::array<std::pair<int, int>, QTY>&);
int random(const int, const int);

#endif
