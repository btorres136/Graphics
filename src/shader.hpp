#ifndef __shader__
#define __shader__

#include <GL/glew.h>
#include <string>

class Shader 
{
  public:
    Shader(const char* vertex_file, const char* fragment_file);

    void Activate();
    void Delete();
    GLuint id();
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
  private: 
    GLuint id_;


};

#endif