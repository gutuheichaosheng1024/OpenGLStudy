#include "VertexArray.h"
#include "GL/glew.h"
#include<iostream>


VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_RenderID);
}


VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_RenderID);
}

void VertexArray::Bind() {
	glBindVertexArray(m_RenderID);
}


void VertexArray::UnBind() {
	glBindVertexArray(0);
}

void VertexArray::ApplyLayout() {
	Bind();
	unsigned int offset = 0;
	for (int i = 0; i < layout.Layout.size(); i++) {
		const auto element = layout.Layout[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, GL_FALSE, layout.GetStride(), (const void*)offset);
		offset += element.count * element.GetType(element.type);
	}
}