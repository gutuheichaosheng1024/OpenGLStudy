#pragma once
#include "GL/glew.h"

class IndexBuffer {
public:
	unsigned int m_RenderID;
	IndexBuffer();
	~IndexBuffer();
	void Bind();
	void UnBind();
	void offerData(size_t size, const void* data, GLuint type);
};
