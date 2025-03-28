#ifndef __PLAYER__
#define __PLAYER__

#include <SDL2/SDL.h>

enum Directions
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct PlayerDeltas 
{
    float deltaX;
    float deltaY;
    int angle;
    float radians;
    float rayX;
    float rayY;
    PlayerDeltas() :
        deltaX(0),
        deltaY(0),
        angle(0),
        radians(0),
        rayX(0),
        rayY(0)
    {}
};

class Player 
{
public:
    Player();
    ~Player();
    void movePlayer(Directions direction);
    void renderPlayer(SDL_Renderer * renderer);
    int getX();
    int getY();
    void calculateRays(SDL_Renderer * renderer);
private:
    SDL_FRect m_player;
    PlayerDeltas m_playerDeltas;

};

#endif