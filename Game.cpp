#include "game.hpp"
#include <iostream>

int map[] = 
{
    1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1
};

Game::Game() :
    is_running_(false),
    renderer_(nullptr),
    window_(nullptr)
{}

Game::~Game()
{
    if(renderer_)
    {
        renderer_ = nullptr;
    }
    if(window_)
    {
        window_ = nullptr;
    }
}

void Game::Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    window_x_size_ = width;
    window_y_size_ = height;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window_ = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window_)
        {
            std::cout << "Window Created!" << std::endl;
        }
        renderer_ = SDL_CreateRenderer(window_, -1, 0);
        if(renderer_)
        {
            std::cout << "Renderer Created!" << std::endl;
        }
        is_running_ = true;
    }
    else
    {
        is_running_ = false;
    }
}

void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    const Uint8 *keys = SDL_GetKeyboardState(nullptr);
    switch(event.type)
    {
        case SDL_QUIT:
            is_running_ = false;
            break;
        case SDL_KEYDOWN:
            if(keys[SDL_SCANCODE_W] == 1)
            {
                player_.MovePlayer(Directions::UP);
            }
            else if(keys[SDL_SCANCODE_S] == 1) 
            {
                player_.MovePlayer(Directions::DOWN);
            }
            else if(keys[SDL_SCANCODE_A] == 1)
            {
                player_.MovePlayer(Directions::LEFT);
            }
            else if(keys[SDL_SCANCODE_D] == 1)
            {
                player_.MovePlayer(Directions::RIGHT);
            }
            break;
        default:
            break;
    }
}

void Game::Update()
{

}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer_, 0,0,0,255);
    SDL_RenderClear(renderer_);
    //this is where we would add stuff to render
    /*int blockXSize = m_windowXSize / 8;
    int blockYSize = m_windowYSize / 8;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(map[x*8+y] == 1)
            { 
                SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255);
            }
            SDL_Rect rect;
            rect.h = blockYSize;
            rect.w = blockXSize;
            rect.x = blockXSize*y;
            rect.y = blockYSize*x;
            SDL_RenderFillRect(m_renderer, &rect);
        }
    }*/
    player_.RenderPlayer(renderer_);
    //////////////////////////////////////////////
    SDL_RenderPresent(renderer_);
}


void Game::Clean()
{
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    SDL_Quit();
    std::cout << "Game Cleaned!" << std::endl;
}

bool Game::is_running()
{
    return is_running_;
}