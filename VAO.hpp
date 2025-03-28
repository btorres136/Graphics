#ifndef __vao__
#define __vao__
#include <GL/glew.h>
#include "VBO.hpp"

class VAO {
  public:
    VAO();
    ~VAO();
    void linkVBO(VBO& vbo, GLuint layout);
    void bind();
    void unbind();
    void remove();

  private:
    GLuint m_id;

};


#endif