#pragma once
#include "glm/glm.hpp"
#include <memory>

class Square
{
public:
	Square(const glm::vec2& first, const glm::vec2& second)
		: m_First(first), m_Second(second)
	{
		Setup();
	}
	void Render();

	const std::pair<glm::vec2, glm::vec2> GetPositions() const {return {m_First, m_Second}; }
	void SetPositions(const glm::vec2& first, const glm::vec2& second);

private:
	void Setup();

public:
	glm::vec2 m_First;
	glm::vec2 m_Second;

	unsigned int m_VertexBufferID;
	unsigned int m_IndexBufferID;
	unsigned int m_VertexArray;
};