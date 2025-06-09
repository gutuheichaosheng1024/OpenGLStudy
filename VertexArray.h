#pragma once
#include "BufferLayout.h"


class VertexArray {
public:
	unsigned int m_RenderID;
	BufferLayout layout;
	VertexArray();
	~VertexArray();
	void Bind();
	void UnBind();
	void ApplyLayout();
};
