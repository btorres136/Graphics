#include "game.hpp"
#include "game_gl.hpp"

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
    game->Init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, false);
    game->Update();
    while(game->is_running())
    {
        game->HandleEvents();
        //game->update();
        game->Render();
    }
    game->Clean();
    #endif

    return 0;
}