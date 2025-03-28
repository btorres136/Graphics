#ifndef __ebo__
#define __ebo__

#include <GL/glew.h>

class EBO 
{
  public:
    EBO(GLuint* indices, GLsizeiptr size);
    void bind();
    void unbind();
    void remove();
  private:
    GLuint m_id;
};
#endif