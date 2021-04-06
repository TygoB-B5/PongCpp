#include "Square.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void Square::Render()
{
	glBindVertexArray(m_VertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Square::SetPositions(const glm::vec2& first, const glm::vec2& second)
{
	m_First = first;
	m_Second = second;

	float vertices[8] =
	{
		m_First.x, m_First.y,
		m_Second.x, m_First.y,
		m_Second.x, m_Second.y,
		m_First.x, m_Second.y
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Square::Setup()
{
	float vertices[8] =
	{
		m_First.x, m_First.y,
		m_Second.x, m_First.y,
		m_Second.x, m_Second.y,
		m_First.x, m_Second.y
	};

	int indices[6] =
	{
		0, 1, 2, 2, 3, 0
	};

	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);

	glGenBuffers(1, &m_VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glGenBuffers(1, &m_IndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
