#include "Game.hpp"
#include "GameGL.hpp"
#define GL

int main(int agrc, char * argv[])
{
    #ifndef GL
    Game *game = new Game();
    game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, false);
    while(game->isRunning())
    {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();
    #else
    GameGL *game = new GameGL();
    game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, false);
    game->update();
    while(game->isRunning())
    {
        game->handleEvents();
        //game->update();
        game->render();
    }
    game->clean();
    #endif

    return 0;
}