#include "Game.h"

int main ()
{
    Game::GameState state;

    if (!Game::init (state))
        return -1;

    Game::run (state);

    return 0;
}