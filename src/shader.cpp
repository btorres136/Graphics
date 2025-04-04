#include "shader.hpp"
#include "utils.hpp"

Shader::Shader(const char* vertex_file, const char* fragment_file)
{
  std::string vertex_code = ReadFile(vertex_file);
  std::string fragment_code = ReadFile(fragment_file);

  const char* vertex_source = vertex_code.c_str();
  const char* fragment_source = fragment_code.c_str();

  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_source, NULL);
  glCompileShader(vertex_shader);

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_source, NULL);
  glCompileShader(fragment_shader);

  id_ = glCreateProgram();
  glAttachShader(id_, vertex_shader);
  glAttachShader(id_, fragment_shader);

  glLinkProgram(id_);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void Shader::Activate()
{
  glUseProgram(id_);
}

void Shader::Delete()
{
  glDeleteProgram(id_);
}

GLuint Shader::id()
{
  return id_;
}

void Shader::setBool(const std::string &name, bool value)
{
  glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value)
{
  glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value)
{
  glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}