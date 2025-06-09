#include "VertexBuffer.h"



VertexBuffer::VertexBuffer() {

    glGenBuffers(1, &m_RenderID);

    
}

void VertexBuffer::offerData(size_t size, const void* data, GLuint type) {
    glBufferData(GL_ARRAY_BUFFER, size, data, type);
}

VertexBuffer::~VertexBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_RenderID);
}



void VertexBuffer::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
}


void VertexBuffer::UnBind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
