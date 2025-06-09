#pragma once
#include "GL/glew.h"

class VertexBuffer {
public:
	unsigned int m_RenderID;
	VertexBuffer();
	~VertexBuffer();
	void Bind();
	void UnBind();
	void offerData(size_t size, const void* data, GLuint type);
};
