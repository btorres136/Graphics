#ifndef __vbo__
#define __vbo__

#include <GL/glew.h>

class VBO {
  public:
    VBO(GLfloat* vertices, GLsizeiptr size);
    void Bind();
    void Unbind();
    void Delete();
  private:
    GLuint id_;
};

#endif