#ifndef __GAME_GL__
#define __GAME_GL__
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"

class GameGL
{
public:
    GameGL();
    ~GameGL();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning();

private:
    bool m_isRunning;
    SDL_Window *m_window;
    SDL_GLContext m_glContext;
    VAO *m_vao;
    VBO *m_vbo;
    EBO *m_ebo;

    int m_windowXSize;
    int m_windowYSize;

};

#endif