#pragma once
#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input.h"
#include "Core.h"
#include "Renderer.h"

class Pong
{
public:
	Pong();
	~Pong();

	void Run();

private:
	void Init();
	void OnUpdate(float deltaTime);
	void CalculateMovement(const float& deltaTime);
	void CalculateBallMovement(const float& deltaTime);
	void CheckWin();

private:
	std::shared_ptr<Input> m_Input;
	std::shared_ptr<Renderer> m_Renderer;
	std::vector<Square> m_Pads;
	Square* m_Cube;
	GLFWwindow* m_Window;
	float m_OldTime = 0;

	unsigned short m_Width = 1280;
	unsigned short m_Height = 720;
	const char* m_Name = "Pong";

	bool isGoingRight = false;
	bool isGoingUp = false;
	int m_RandomSpeed = 0;
	int m_Speed = 500;

	bool m_Running = true;
};