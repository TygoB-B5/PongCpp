#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

Renderer::Renderer()
{
	m_ShaderID = glCreateProgram();
}

void Renderer::Init()
{
	std::string vertexSource = m_VertexShader;
	std::string fragmentSource = m_FragmentShader;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* source = (const GLchar*)vertexSource.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		std::string error;
		for (auto& c : infoLog)
			error += c;

		ASSERT(false, error)

			glDeleteShader(vertexShader);
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* source2 = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &source2, 0);

	glCompileShader(fragmentShader);

	GLint isCompiled2 = 0;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled2);
	if (isCompiled2 == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		std::string error;
		for (auto& c : infoLog)
			error += c;

		ASSERT(false, error)

		glDeleteShader(fragmentShader);
	}

	glAttachShader(m_ShaderID, vertexShader);
	glAttachShader(m_ShaderID, fragmentShader);
	glLinkProgram(m_ShaderID);

	glUseProgram(m_ShaderID);
	GLuint MatrixID = glGetUniformLocation(m_ShaderID, "m_TransformMatrix");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(m_TranformMatrix));

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(m_ShaderID);

	glfwSwapInterval(0);
}

void Renderer::AddSquare(const Square& square)
{
	m_Squares.push_back(square);
}

void Renderer::OnUpdate()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_ShaderID);
	for (Square& square : m_Squares)
	{
		square.Render();
	}
}
