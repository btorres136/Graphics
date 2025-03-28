#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>
#include <vector>
#include "Player.hpp"
#include "Map.hpp"

class Game 
{
public:
    Game();
    ~Game();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning();

private:
    bool m_isRunning;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    int m_windowXSize;
    int m_windowYSize;
    Player m_player;

};

#endif