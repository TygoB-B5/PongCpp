#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Core.h"
#include <array>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Square.h"

class Renderer
{
public:
	Renderer();
	void Init();
	void AddSquare(const Square& verticies);

	void OnUpdate();

private:
	std::vector<Square> m_Squares;

	std::pair<int, int> AspectRatio = { 16, 9 };
	glm::mat4 m_TranformMatrix = glm::ortho(-1280.0f / 2, 1280.0f / 2, -720.0f / 2, 720.0f / 2);

	unsigned int m_ShaderID;

	std::string m_VertexShader = R"(
#version 330 core

layout (location = 0) in vec3 u_Position;

uniform mat4 m_TransformMatrix;

void main()
{
    gl_Position = m_TransformMatrix * vec4(u_Position, 1.0);
}
)";

	std::string m_FragmentShader = R"(
#version 330 core

layout (location = 0) out vec4 o_Color;

void main() {

o_Color = vec4(1.0, 1.0, 1.0, 1.0);
}
)";
};