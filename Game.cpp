#include "Game.hpp"
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
    m_isRunning(false),
    m_renderer(nullptr),
    m_window(nullptr)
{}

Game::~Game()
{
    if(m_renderer)
    {
        m_renderer = nullptr;
    }
    if(m_window)
    {
        m_window = nullptr;
    }
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    m_windowXSize = width;
    m_windowYSize = height;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(m_window)
        {
            std::cout << "Window Created!" << std::endl;
        }
        m_renderer = SDL_CreateRenderer(m_window, -1, 0);
        if(m_renderer)
        {
            std::cout << "Renderer Created!" << std::endl;
        }
        m_isRunning = true;
    }
    else
    {
        m_isRunning = false;
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    const Uint8 *keys = SDL_GetKeyboardState(nullptr);
    switch(event.type)
    {
        case SDL_QUIT:
            m_isRunning = false;
            break;
        case SDL_KEYDOWN:
            if(keys[SDL_SCANCODE_W] == 1)
            {
                m_player.movePlayer(Directions::UP);
            }
            else if(keys[SDL_SCANCODE_S] == 1) 
            {
                m_player.movePlayer(Directions::DOWN);
            }
            else if(keys[SDL_SCANCODE_A] == 1)
            {
                m_player.movePlayer(Directions::LEFT);
            }
            else if(keys[SDL_SCANCODE_D] == 1)
            {
                m_player.movePlayer(Directions::RIGHT);
            }
            break;
        default:
            break;
    }
}

void Game::update()
{

}

void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 0,0,0,255);
    SDL_RenderClear(m_renderer);
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
    m_player.renderPlayer(m_renderer);
    //////////////////////////////////////////////
    SDL_RenderPresent(m_renderer);
}


void Game::clean()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
    std::cout << "Game Cleaned!" << std::endl;
}

bool Game::isRunning()
{
    return m_isRunning;
}