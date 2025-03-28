#include "ebo.hpp"

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
  glGenBuffers(1, &id_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void EBO::Unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
  glDeleteBuffers(1, &id_);
}

