#pragma once

#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

struct VertexBufferElement 
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) 
	{
		switch (type) 
		{
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout 
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride = 0; // The stride is the size of the vertex buffer
public:
	VertexBufferLayout() 
		: m_Stride(0)
	{}
	~VertexBufferLayout() {}

	template<typename T>
	void Push(unsigned int count)
	{
		// static_assert(false); // This will always fail
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE }); // Add a float element to the vector
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT); // Increase the stride by the size of the float
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE }); // Add a unsigned char element to the vector
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT); // Increase the stride by the size of the unsigned int
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE }); // Add a unsigned char element to the vector
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE); // Increase the stride by the size of the unsigned char
	}
	
	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride;  }
};