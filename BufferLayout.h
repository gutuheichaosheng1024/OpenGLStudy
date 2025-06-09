#pragma once
#include "GL/glew.h"
#include <stdexcept>
#include<vector>
#include<iostream>

class BufferElement {
public:
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
	BufferElement(unsigned int _type, unsigned int _count, unsigned char _normalized) {
		type = _type;
		count = _count;
		normalized = _normalized;
	}

	static unsigned int GetType(unsigned int type) {
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		default:
			break;
		}
		throw std::invalid_argument("¥ÌŒÛµƒ¿‡–Õ");
	}
};

class BufferLayout {
public:
	std::vector<BufferElement>Layout;
	unsigned int m_Stride;

	template<typename T>
	void Push(unsigned int count) {
		//static_assert(always_false<T>, "Only float specialization is allowed");
	}

	template<>
	void Push<float>(unsigned int count) {
		BufferElement newElement(GL_FLOAT, count, GL_FALSE);
		Layout.push_back(newElement);
		m_Stride += (count * BufferElement::GetType(GL_FLOAT));
	}

	inline const std::vector<BufferElement> GetElements() const { return  Layout; };
	inline unsigned int GetStride() const { return m_Stride; };
};


