#ifndef __shader__
#define __shader__

#include <GL/glew.h>

class Shader 
{
  public:
    Shader(const char* vertex_file, const char* fragment_file);

    void Activate();
    void Delete();
  private: 
    GLuint id_;


};

#endif