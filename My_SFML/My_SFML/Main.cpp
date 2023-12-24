#include <iostream>
#include "Game.h"

int main()
{
    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init game
    Game game;


    while (game.running() && !game.getEndGame())
    {
        // Update
        game.update();


        // render
        game.render();
    }

    // and of aplication
    return 0;
}