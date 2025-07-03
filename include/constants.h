#ifndef CONSTANTS_H
#define CONSTANTS_H

inline constexpr bool WINDOWS =  true;

inline constexpr int DUNGEON_SIZE = 8;
inline constexpr int START_VAL = 0;
inline constexpr int END_VAL = 7;
inline constexpr int QTY = 14;
inline constexpr int NUM_PITS = 8;
inline constexpr int NUM_EVIL = 1;
inline constexpr int NUM_GOLD = 1;
inline constexpr std::pair<int, int> INIT_COORD = {0, 0};

inline constexpr char STENCH = 'S';
inline constexpr char BREEZE = 'B';
inline constexpr char GLIMMER = 'G';
inline constexpr char EMPTY = '.';
inline constexpr char PIT = 'P';
inline constexpr char EVIL = 'E';

#endif // CONSTANTS_H
