#ifndef __MAP__
#define __MAP__

#include <SDL2/SDL.h>

class Map
{
public:
    Map();
    ~Map();
    void setSize(int high, int width);
    void RenderMap(SDL_Renderer* renderer);
private:
    int *map_;
};

#endif