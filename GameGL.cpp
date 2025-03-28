#include "GameGL.hpp"
#include <iostream>

/*

See link: 
https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%204%20-%20Organizing/Main.cpp

*/


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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
    m_isRunning(false),
    m_window(nullptr)
{}

GameGL::~GameGL()
{
    if(m_window)
    {
        m_window = nullptr;
    }
}

void GameGL::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
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
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        m_window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL | flags);
        if(m_window)
        {
            std::cout << "Window Created!" << std::endl;
        }
        m_glContext = SDL_GL_CreateContext(m_window);
        if(m_glContext)
        {
            std::cout << "GL Context Created!" << std::endl;
        }
        SDL_GL_SetSwapInterval(1);
        if(glewInit() == GLEW_OK)
        {
            std::cout << "GLEW initialized" << std::endl;
        }
        m_isRunning = true;
    }
    else
    {
        m_isRunning = false;
    }
}

void GameGL::handleEvents()
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

void GameGL::update()
{
    m_vao = new VAO();
    m_vao->bind();

    m_vbo = new VBO(vertices, sizeof(vertices));
    m_vao->linkVBO(*m_vbo, 0);

    m_ebo = new EBO(indices, sizeof(indices));

    m_vao->unbind();
    m_vbo->unbind();
    m_ebo->unbind();
}

void GameGL::render()
{
    //Background color
    glClearColor(0.7f, 0.13f, 0.17f, 1.0f);
    //Clean the back buffer and assing the new color
    glClear(GL_COLOR_BUFFER_BIT);

    m_vao->bind();

    //Draw the triangle using the GL_TRIANGLE primitives
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    // Take care of all GLFW events
    SDL_GL_SwapWindow(m_window);
}


void GameGL::clean()
{
    //glDeleteProgram(shaderProgam);
    m_vao->remove();
    m_vbo->remove();
    m_ebo->remove();

    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    std::cout << "Game Cleaned!" << std::endl;
}

bool GameGL::isRunning()
{
    return m_isRunning;
}

