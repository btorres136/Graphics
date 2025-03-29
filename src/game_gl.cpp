#include <iostream>
#include "game_gl.hpp"

/*

See link: 
https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%204%20-%20Organizing/Main.cpp

*/

// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

GameGL::GameGL() :
    is_running_(false),
    window_(nullptr)
{}

GameGL::~GameGL()
{
    if(window_)
    {
        window_ = nullptr;
    }
}

void GameGL::Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
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
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        window_ = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL | flags);
        if(window_)
        {
            std::cout << "Window Created!" << std::endl;
        }
        gl_context_ = SDL_GL_CreateContext(window_);
        if(gl_context_)
        {
            std::cout << "GL Context Created!" << std::endl;
        }
        SDL_GL_SetSwapInterval(1);
        if(glewInit() == GLEW_OK)
        {
            std::cout << "GLEW initialized" << std::endl;
        }
        is_running_ = true;
    }
    else
    {
        is_running_ = false;
    }
}

void GameGL::HandleEvents()
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
            }
            else if(keys[SDL_SCANCODE_S] == 1) 
            {
            }
            else if(keys[SDL_SCANCODE_A] == 1)
            {
            }
            else if(keys[SDL_SCANCODE_D] == 1)
            {
            }
            break;
        default:
            break;
    }
}

void GameGL::Update()
{
    shader_program_ = new Shader("../shaders/default/default.vert", "../shaders/default/default.frag");
    vao_ = new VAO();
    vao_->Bind();

    vbo_ = new VBO(vertices, sizeof(vertices));
    vao_->LinkVBO(*vbo_, 0);

    ebo_ = new EBO(indices, sizeof(indices));

    vao_->Unbind();
    vbo_->Unbind();
    ebo_->Unbind();
}

void GameGL::Render()
{
    //Background color
    glClearColor(0, 0, 0, 0);
    //Clean the back buffer and assing the new color
    glClear(GL_COLOR_BUFFER_BIT);

    shader_program_->Activate(); 

    vao_->Bind();

    //Draw the triangle using the GL_TRIANGLE primitives
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    // Take care of all GLFW events
    SDL_GL_SwapWindow(window_);
}


void GameGL::Clean()
{
    //glDeleteProgram(shaderProgam);
    vao_->Delete();
    vbo_->Delete();
    ebo_->Delete();

    SDL_GL_DeleteContext(gl_context_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
    std::cout << "Game Cleaned!" << std::endl;
}

bool GameGL::is_running()
{
    return is_running_;
}

