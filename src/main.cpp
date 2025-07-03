#include <array>
#include <ctime>
#include "Dungeon.h"
#include "GameWindow.h"

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    std::array<std::array<Tile, DUNGEON_SIZE>, DUNGEON_SIZE> dungeon;
    setUpDungeon(dungeon);

    GameWindow game;
    game.run(dungeon);

    return 0;
}
