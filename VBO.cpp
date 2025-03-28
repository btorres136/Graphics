#include "vbo.hpp"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
  glGenBuffers(1, &id_);
  glBindBuffer(GL_ARRAY_BUFFER, id_);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void VBO::Unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void VBO::Delete()
{
  glDeleteBuffers(1, &id_);
}