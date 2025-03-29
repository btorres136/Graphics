#ifndef __GAME_GL__
#define __GAME_GL__
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <vector>
#include "vbo.hpp"
#include "vao.hpp"
#include "ebo.hpp"
#include "shader.hpp"

class GameGL
{
public:
    GameGL();
    ~GameGL();
    void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    bool is_running();

private:
    bool is_running_;
    SDL_Window *window_;
    SDL_GLContext gl_context_;
    VAO *vao_;
    VBO *vbo_;
    EBO *ebo_;
    Shader *shader_program_;

    int window_x_size_;
    int window_y_size_;

};

#endif