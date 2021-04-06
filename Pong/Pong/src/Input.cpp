#include "Input.h"


static int ConvertToGlKeycode(int key)
{
	switch (key)
	{
	case KEY_W: return GLFW_KEY_W;
	case KEY_S: return GLFW_KEY_S;
	case KEY_UPARROW: return GLFW_KEY_UP;
	case KEY_DOWNARROW: return GLFW_KEY_DOWN;
	case KEY_SPACE: return GLFW_KEY_SPACE;
	}
}

void Input::InitKeys(GLFWwindow* window)
{
	m_WindowHandle = window;
}

bool Input::IsKeyPressed(int key) const
{
	return glfwGetKey(m_WindowHandle, ConvertToGlKeycode(key));
}
