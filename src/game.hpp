#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>
#include <vector>
#include "player.hpp"
#include "map.hpp"

class Game 
{
public:
    Game();
    ~Game();
    void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    bool is_running();

private:
    bool is_running_;
    SDL_Window *window_;
    SDL_Renderer *renderer_;
    int window_x_size_;
    int window_y_size_;
    Player player_;

};

#endif