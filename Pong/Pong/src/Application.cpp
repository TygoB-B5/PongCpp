#include "Application.h"
#include "Square.h"

Pong::Pong()
{
	Init();
}

Pong::~Pong()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Pong::Init()
{
	glfwInit();
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);
	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		ASSERT(false, "Failed to initialize GLAD");
	}

	m_Input.reset(new Input());
	m_Renderer.reset(new Renderer());

	m_Input->InitKeys(m_Window);
	m_Renderer->Init();


	Square square = Square({ (-1280/2), (-720/2) }, { (1280/2), (-620/2) });
	m_Renderer->AddSquare(square);
	Square square2 = Square({ (-1280 / 2), (720 / 2) }, { (1280 / 2), (620 / 2) });
	m_Renderer->AddSquare(square2);
	Square pad1 = Square({ (-1200 / 2), -75}, { (-1180 / 2), 75});
	m_Renderer->AddSquare(pad1);
	Square pad2 = Square({ (1200 / 2), -75 }, { (1180 / 2), 75 });
	m_Renderer->AddSquare(pad2);

	m_Cube = new Square({ -10, -10 }, { 10, 10 });
	m_Renderer->AddSquare(*m_Cube);

	m_Pads.push_back(pad1);
	m_Pads.push_back(pad2);
}


void Pong::Run()
{	

	PRINT("Use W and S for left paddle");
	PRINT("Use UPARROW and DOWNARROW for right paddle");

	while (m_Running)
	{
		glfwPollEvents();

		float deltaTime = glfwGetTime() - m_OldTime;
		m_OldTime = glfwGetTime();
		OnUpdate(deltaTime);
		glfwSwapBuffers(m_Window);
	}
}


void Pong::CalculateMovement(const float& deltaTime)
{
	const int speed = 1000;
	if (m_Input->IsKeyPressed(KEY_W) && m_Pads[0].GetPositions().second.y < (720 / 2))
	{
		glm::vec2 newPos[2];
		newPos[0] = { m_Pads[0].GetPositions().first.x, m_Pads[0].GetPositions().first.y + speed * deltaTime };
		newPos[1] = { m_Pads[0].GetPositions().second.x, m_Pads[0].GetPositions().second.y + speed * deltaTime };
		m_Pads[0].SetPositions(newPos[0], newPos[1]);
	}

	if (m_Input->IsKeyPressed(KEY_S) && m_Pads[0].GetPositions().first.y > (-720 / 2))
	{
		glm::vec2 newPos[2];
		newPos[0] = { m_Pads[0].GetPositions().first.x, m_Pads[0].GetPositions().first.y + -speed * deltaTime };
		newPos[1] = { m_Pads[0].GetPositions().second.x, m_Pads[0].GetPositions().second.y + -speed * deltaTime };
		m_Pads[0].SetPositions(newPos[0], newPos[1]);
	}

	if (m_Input->IsKeyPressed(KEY_UPARROW) && m_Pads[1].GetPositions().second.y < (720 / 2))
	{
		glm::vec2 newPos[2];
		newPos[0] = { m_Pads[1].GetPositions().first.x, m_Pads[1].GetPositions().first.y + speed * deltaTime };
		newPos[1] = { m_Pads[1].GetPositions().second.x, m_Pads[1].GetPositions().second.y + speed * deltaTime };
		m_Pads[1].SetPositions(newPos[0], newPos[1]);
	}

	if (m_Input->IsKeyPressed(KEY_DOWNARROW) && m_Pads[1].GetPositions().first.y > (-720 / 2))
	{
		glm::vec2 newPos[2];
		newPos[0] = { m_Pads[1].GetPositions().first.x, m_Pads[1].GetPositions().first.y + -speed * deltaTime };
		newPos[1] = { m_Pads[1].GetPositions().second.x, m_Pads[1].GetPositions().second.y + -speed * deltaTime };
		m_Pads[1].SetPositions(newPos[0], newPos[1]);
	}
}

void Pong::CalculateBallMovement(const float& deltaTime)
{
	glm::vec2 cubeFirst = m_Cube->GetPositions().first;
	glm::vec2 cubeSecond = m_Cube->GetPositions().second;

	float addX = 0;
	float addY = 0;

	m_Speed += deltaTime * 10;

	if(cubeSecond.y > (720/2))
		isGoingUp = false;
	if (cubeFirst.y < -(720 / 2))
		isGoingUp = true;

	if (isGoingUp)
		addY = m_RandomSpeed;
	else
		addY = -m_RandomSpeed;

	
	if (isGoingRight)
		addX = m_Speed;
	else
		addX = -m_Speed;

	if (cubeSecond.y > m_Pads[0].GetPositions().first.y &&
		cubeFirst.y < m_Pads[0].GetPositions().second.y &&
		cubeFirst.x < m_Pads[0].GetPositions().first.x)
	{
		isGoingRight = true;
		m_RandomSpeed = rand() % m_Speed;
	}

	if (cubeSecond.y > m_Pads[1].GetPositions().first.y &&
		cubeFirst.y < m_Pads[1].GetPositions().second.y &&
		cubeFirst.x > m_Pads[1].GetPositions().first.x - 20.0f)
	{
		isGoingRight = false;
		m_RandomSpeed = rand() % m_Speed;
	}

	cubeFirst.x += addX * deltaTime;
	cubeSecond.x += addX * deltaTime;
	cubeFirst.y += addY * deltaTime;
	cubeSecond.y += addY * deltaTime;

	m_Cube->SetPositions(cubeFirst, cubeSecond);
}

void Pong::CheckWin()
{
	glm::vec2 cubeFirst = m_Cube->GetPositions().first;
	if (cubeFirst.x < -1280 / 2 - 10)
	{
		PRINT("Left Won");
		glfwTerminate();
		m_Running = false;
		system("pause");
	}

	if (cubeFirst.x > 1280 / 2 + 10)
	{
		PRINT("Right Won");
		glfwTerminate();
		m_Running = false;
		system("pause");
	}
}

void Pong::OnUpdate(float deltaTime)
{
	CalculateMovement(deltaTime);
	CalculateBallMovement(deltaTime);
	CheckWin();
	m_Renderer->OnUpdate();
}