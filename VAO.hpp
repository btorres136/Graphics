#ifndef __vao__
#define __vao__
#include <GL/glew.h>
#include "vbo.hpp"

class VAO {
  public:
    VAO();
    ~VAO();
    void LinkVBO(VBO& vbo, GLuint layout);
    void Bind();
    void Unbind();
    void Delete();

  private:
    GLuint id_;

};


#endif