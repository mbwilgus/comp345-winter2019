#include <iostream>
using namespace std;

#include "Game.h"

int main(int argc, char *argv[])
{
    Game* game = Game::buildGame();
    cout << game->playerInfo() << endl;
    delete game;
    return 0;
}
