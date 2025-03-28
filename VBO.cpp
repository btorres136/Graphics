#include "VBO.hpp"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VBO::unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VBO::remove()
{
  glDeleteBuffers(1, &m_id);
}