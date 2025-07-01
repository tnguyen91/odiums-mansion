// who: Tu Nguyen, mnguyen207
// what: Odium’s Mansion 
// why: lab exam 2
// when: <the due date of this lab.>

#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <stdlib.h>

#include "odiums_mansion.h"

int main(int argc, char const *argv[])
{
    srand(static_cast<unsigned int> (time(0)));

    std::array<std::array<char, DUNGEON_SIZE>, DUNGEON_SIZE> dungeon {0};
    setUpDungeon(dungeon, getDungeonCoord());
    
    play(dungeon);
    return 0;
}

std::array<std::pair<int, int>, QTY> getDungeonCoord(){
    std::array<std::pair<int, int>, QTY> coord;
    std::pair<int, int> p;

    for (std::pair<int, int>& c : coord){
        p = std::make_pair(random(START_VAL, END_VAL), random(START_VAL, END_VAL));
        while (p.first + p.second < 2 || std::find(coord.begin(), coord.end(), p) != coord.end()){
            p = std::make_pair(random(START_VAL, END_VAL), random(START_VAL, END_VAL));
        }
        c = p;
    }
    return coord;
}

void setUpDungeon(std::array<std::array<char, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon, const std::array<std::pair<int, int>, QTY>& dungeonCoord){
    dungeon[dungeonCoord[0].first][dungeonCoord[0].second] = GLIMMER;
    dungeon[dungeonCoord[1].first][dungeonCoord[1].second] = STENCH;
    for (int i = 2; i < dungeonCoord.size(); ++i){
        dungeon[dungeonCoord[i].first][dungeonCoord[i].second] = BREEZE;
    }
}

void play(const std::array<std::array<char, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon){
    Player p;
    bool goldTaken = false;
    p.printGrid(goldTaken); 
    while (notWin(p.getCoord(), goldTaken) && notLose(p.getCoord(), dungeon))
    {
        p.validMove(goldTaken);
        p.sense(dungeon);
        p.printGrid(goldTaken);
    }
}

bool notWin(const std::pair<int, int>& playersCoord, const bool goldTaken){
    std::pair<int, int> initCoord {INIT_COORD};
    if (playersCoord == initCoord && goldTaken) {
        std::cout << "You've escaped with the gold, well done!\n";
        return false;
    }
    return true;
}

bool notLose(const std::pair<int, int>& playersCoord, const std::array<std::array<char, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon){
    if (dungeon[playersCoord.first][playersCoord.second] == STENCH || dungeon[playersCoord.first][playersCoord.second] == BREEZE){
        std::cout << "You have died in the dungeon of the evil Aldrac, cursed be his name!\n";
        return false;
    }
    return true;
}

Player::Player()
{
    playersCoord = std::make_pair(INIT_COORD);
    
    for (int i = 0;i < DUNGEON_SIZE; ++i){
        for (int j = 0; j < DUNGEON_SIZE; ++j){
            log[i][j] = "     ";
        }
    }
}

std::pair<int, int> Player::getCoord(){
    return playersCoord;
}

void Player::printGrid(const bool goldTaken){
    clearScreen();
    int rowCnt = -1;
    bool logOrU = false;
    for (int i = 0; i < DUNGEON_SIZE * 3 + 1; ++i){
        int colCnt = -1;
        if (i % 3 == 0) ++rowCnt;
        else logOrU = !logOrU;
        for (int j = 0; j < DUNGEON_SIZE + (DUNGEON_SIZE + 1); ++j){
            if (i % 3 == 0) std::cout << (j % 2 == 0 ? "-" : "-----");
            else {
                if (!(j%2)){
                    std::cout << '|';
                    ++colCnt;
                }
                else std::cout << getCeil(rowCnt, colCnt, logOrU, goldTaken);
            }
        }
        std::cout << '\n';
    }
    std::cout << (goldTaken && playersCoord != std::make_pair(INIT_COORD) ? "You are holding gold.\n" : "");
}

std::string Player::getCeil(const int row, const int col, const bool printLog, const bool goldTaken){
    if (printLog){
        if (goldTaken) log[row][col][4] = ' ';
        return log[row][col];
    }
    else{
        std::pair<int, int> u = std::make_pair(row, col);
        return (u == playersCoord ? "  U  " : "     ");
    }
}

void Player::validMove(bool& goldTaken){
    std::cout << "Enter Your move\n(R)ight, (L)eft, (U)p, (D)own, (P)ickup gold: ";
    char c;
    std::cin >> c;
    clearInstream();
    c = tolower(c);
    while (!isValidMove(c, goldTaken)){
        std::cout << "That is not a valid option!\n";
        std::cout << "Enter Your move\n(R)ight, (L)eft, (U)p, (D)own, (P)ickup gold: ";
        std::cin >> c;
        c = tolower(c);
    }
}

bool Player::isValidMove(const char c, bool& goldTaken){
    if(c == 'r' || c == 'l' || c == 'u' || c == 'd' || c == 'p'){
        std::pair<int, int> oldCoord = playersCoord;
        switch (c){
        case 'u':
            playersCoord.first -= (playersCoord.first != START_VAL);
            return playersCoord != oldCoord;
        case 'd':
            playersCoord.first += (playersCoord.first != END_VAL);
            return playersCoord != oldCoord;
        case 'l':
            playersCoord.second -= (playersCoord.second != START_VAL);
            return playersCoord != oldCoord;
        case 'r':
            playersCoord.second += (playersCoord.second != END_VAL);
            return playersCoord != oldCoord;
        default:
            if(log[playersCoord.first][playersCoord.second][4] == GLIMMER){
                goldTaken = true;
                return true;
            }
        }
    }
    return false;
}

void Player::sense(const std::array<std::array<char, DUNGEON_SIZE>, DUNGEON_SIZE>& dungeon){
    if ((playersCoord.first + 1) <= END_VAL && (dungeon[playersCoord.first + 1][playersCoord.second] != '_' && (dungeon[playersCoord.first + 1][playersCoord.second] != GLIMMER))){
        recordSensation(dungeon[getCoord().first + 1][getCoord().second]);
    }
    if ((playersCoord.first - 1) >= START_VAL && (dungeon[playersCoord.first - 1][playersCoord.second] != '_' && (dungeon[playersCoord.first - 1][playersCoord.second] != GLIMMER))){
        recordSensation(dungeon[playersCoord.first - 1][playersCoord.second]);
    }
    if ((playersCoord.second + 1) <= END_VAL && (dungeon[playersCoord.first][playersCoord.second + 1] != '_' && (dungeon[playersCoord.first][playersCoord.second + 1] != GLIMMER))){
        recordSensation(dungeon[playersCoord.first][playersCoord.second + 1]);
    }
    if ((playersCoord.second - 1) >= START_VAL && (dungeon[playersCoord.first][playersCoord.second - 1] != '_' && (dungeon[playersCoord.first][playersCoord.second - 1] != GLIMMER))){
        recordSensation(dungeon[playersCoord.first][getCoord().second - 1]);
    }
    if (dungeon[playersCoord.first][playersCoord.second] == GLIMMER){

        recordSensation(GLIMMER);
    }
}

void Player::recordSensation(const char c){
    switch (c)
    {
    case STENCH:
        log[playersCoord.first][playersCoord.second][0] = c;
        break;
    case GLIMMER:
        log[playersCoord.first][playersCoord.second][4] = c;
        break;
    case BREEZE:
        log[playersCoord.first][playersCoord.second][2] = c;
        break;
    }
}

void clearScreen()
{
    
    if(WINDOWS)
        system("CLS");
    else
        system("clear");
        
}

void clearInstream()
{
    std::cin.clear();
    // Wrong input remains on the stream, so you need to get rid of it
    std::cin.ignore(INT_MAX, '\n');
}

int random(int start, int end){
    return rand() % (end - start + 1) + start;
}