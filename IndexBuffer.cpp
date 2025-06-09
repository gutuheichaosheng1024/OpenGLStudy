#include "IndexBuffer.h"



IndexBuffer::IndexBuffer() {
    glGenBuffers(1, &m_RenderID);
}


IndexBuffer::~IndexBuffer() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_RenderID);
}


void IndexBuffer::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
}

void IndexBuffer::UnBind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void IndexBuffer::offerData(size_t size, const void* data, GLuint type) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, type);
}