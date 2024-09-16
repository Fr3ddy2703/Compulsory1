#include "pch.h"
#include "initializer.h"

#include "../Input/input.h"
#include "../Shaders/shader.h"

float initializer::DeltaTime = 0.f;
camera initializer::UseCamera = camera();

//float randxpos = rand();

void initializer::Initialize()
{
	window = window::initWindow();
	UseCamera.initCamera();
	
	Run();
}

void initializer::Create()
{

	/* Scene */
	Floor.CreateCube(glm::vec3(18.f, 0.5f, 9.f), glm::vec3(1.f, 0.f, 9.f),Color::Green);
	Floor.AddCollider(Floor.GetScale(), ECollisionType::Boxes);

	/* Left wall */
	Wall.CreateCube(glm::vec3(20.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f),Color::Brown);
	Wall.AddCollider(Wall.GetScale(), ECollisionType::Boxes);

	/* Right wall */
	Wall2.CreateCube(glm::vec3(20.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 10.f),Color::Brown);
	Wall2.AddCollider(Wall2.GetScale(), ECollisionType::Boxes);

	/* Front wall */
	Wall3.CreateCube(glm::vec3(1.f, 1.f, -9.f), glm::vec3(0.f, 0.f, 0.f),Color::Brown);
	Wall3.AddCollider(Wall3.GetScale(), ECollisionType::Boxes);

	/* Back wall */
	Wall4.CreateCube(glm::vec3(1.f, 1.f, -9.f), glm::vec3(19.f, 0.f, 0.f),Color::Brown);
	Wall4.AddCollider(Wall4.GetScale(), ECollisionType::Boxes);

	for (int i = 0; i < 1; i++)
	{
		RollingBall* ball = new RollingBall();
		ball->CreateSphere(glm::vec3(0.25f, 0.25f, 0.25f),4.f, glm::vec3(15.f, 0.75f, 5.f + i), Color::Gold);
		ball->AddCollider(ball->GetScale(), ECollisionType::ball);
		Balls.emplace_back(ball);
	}
	

	Meshes.emplace_back(&Floor);
	Meshes.emplace_back(&Wall);
	Meshes.emplace_back(&Wall2);
	Meshes.emplace_back(&Wall3);
	Meshes.emplace_back(&Wall4);
	Balls.emplace_back(&Sphere);

}

void initializer::Run()
{
	Create();
	float FirstFrame = 0.0f;
	glm::vec3 color(Color::Grey);
	
	while (!glfwWindowShouldClose(window))
	{
		const auto CurrentFrame = static_cast<float>(glfwGetTime());
		DeltaTime = CurrentFrame - FirstFrame;
		FirstFrame = CurrentFrame;

		glClearColor(color.x, color.y, color.z, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(Shader::ShaderProgram);

		KeyBoardInput::processInput(window);
		Update(DeltaTime);

		glEnable(GL_DEPTH);
		glUniformMatrix4fv(UseCamera.projectionLoc, 1, GL_FALSE, glm::value_ptr(UseCamera.getProjection(window::width, window::height)));
		glUniformMatrix4fv(UseCamera.viewLoc, 1, GL_FALSE, glm::value_ptr(UseCamera.getView()));
		glUniform3fv(glGetUniformLocation(Shader::ShaderProgram, "viewPos"), 1, glm::value_ptr(UseCamera.cameraPos));
		for (auto mesh : Meshes)
		{
			mesh->Draw();
		}
		for (auto sphere : Balls)
		{
			sphere->DrawSphere();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

void initializer::Update(float deltaTime)
{
	//Collision::checkCollision();
}

initializer::~initializer()
{
}
