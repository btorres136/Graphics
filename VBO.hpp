#ifndef __vbo__
#define __vbo__

#include <GL/glew.h>

class VBO {
  public:
    VBO(GLfloat* vertices, GLsizeiptr size);
    void bind();
    void unbind();
    void remove();
  private:
    GLuint m_id;
};

#endif