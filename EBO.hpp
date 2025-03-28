#ifndef __ebo__
#define __ebo__

#include <GL/glew.h>

class EBO 
{
  public:
    EBO(GLuint* indices, GLsizeiptr size);
    void Bind();
    void Unbind();
    void Delete();
  private:
    GLuint id_;
};
#endif