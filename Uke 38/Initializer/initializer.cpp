#include "pch.h"
#include "initializer.h"

#include "../Input/input.h"
#include "../Shaders/shader.h"

float initializer::DeltaTime = 0.f;
camera initializer::UseCamera = camera();


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

	/* Left wall */
	Wall.CreateCube(glm::vec3(20.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f),Color::Brown);
	Wall.AddCollider(Wall.GetScale(), ECollisionType::Boxes);

	/* Right wall */
	Wall2.CreateCube(glm::vec3(20.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 10.f),Color::Brown);
	Wall2.AddCollider(Wall2.GetScale(), ECollisionType::Boxes);

	/* Front wall */
	Wall3.CreateCube(glm::vec3(-1.f, 1.f, -9.f), glm::vec3(1.f, 0.f, 0.f),Color::Brown);
	Wall3.AddCollider(Wall3.GetScale(), ECollisionType::Boxes);

	/* Back wall */
	Wall4.CreateCube(glm::vec3(1.f, 1.f, -9.f), glm::vec3(19.f, 0.f, 0.f),Color::Brown);
	Wall4.AddCollider(Wall4.GetScale(), ECollisionType::Boxes);

	RollingBall Sphere;
	Sphere.CreateSphere(glm::vec3(0.25f),4.f, glm::vec3(15.25f, 0.75f, 2.5f), 1.f,glm::vec3(0.f, 0.f, 0.f),Color::Gold);
	Sphere.AddCollider(Sphere.GetScale(), ECollisionType::ball);

	/* Creating the balls */
	RollingBall kule;
	kule.CreateSphere(glm::vec3(0.25f),4.f, glm::vec3(15.f, 0.75f, 7.5f), 1.f,glm::vec3(0.f, 0.f, 0.f),Color::Gold);
	kule.AddCollider(kule.GetScale(), ECollisionType::ball);

	Balls.push_back(kule);


	Meshes.emplace_back(Floor);
	Meshes.emplace_back(Wall);
	Meshes.emplace_back(Wall2);
	Meshes.emplace_back(Wall3);
	Meshes.emplace_back(Wall4);
	Balls.push_back(Sphere);

}

void initializer::Run()
{
	Create();
	float FirstFrame = 0.0f;
	glm::vec3 color(Color::Grey);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_E ) && start == false)
		{
			Balls[0].velocity = glm::vec3(0.0f, 0.0f, 1.0f);
			start = true;
		}
		const auto CurrentFrame = static_cast<float>(glfwGetTime());
		DeltaTime = CurrentFrame - FirstFrame;
		FirstFrame = CurrentFrame;

		glClearColor(color.x, color.y, color.z, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(Shader::ShaderProgram);

		KeyBoardInput::processInput(window);
		Update(DeltaTime);

		glUniformMatrix4fv(UseCamera.projectionLoc, 1, GL_FALSE, glm::value_ptr(UseCamera.getProjection(window::width, window::height)));
		glUniformMatrix4fv(UseCamera.viewLoc, 1, GL_FALSE, glm::value_ptr(UseCamera.getView()));
		glUniform3fv(glGetUniformLocation(Shader::ShaderProgram, "viewPos"), 1, glm::value_ptr(UseCamera.cameraPos));
		for (auto& mesh : Meshes)
		{
			mesh.Draw();
		}
		for (auto& sphere : Balls)
		{
			sphere.DrawSphere();
		}
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

void initializer::Update(float deltaTime)
{
        Collision collision;

	for (auto& mball : Balls)
	{
		if (
		   collision.checkBallBoxCollision(mball, Wall, ECollisionType::ball, ECollisionType::Boxes) ||
		  collision.checkBallBoxCollision(mball, Wall2, ECollisionType::ball, ECollisionType::Boxes) ||
		  collision.checkBallBoxCollision(mball, Wall3, ECollisionType::ball, ECollisionType::Boxes) ||
		  collision.checkBallBoxCollision(mball, Wall4, ECollisionType::ball, ECollisionType::Boxes))
		{
			mball.velocity = -mball.velocity;
		}
		
	}
	for (auto& mball : Balls)
	{

		if(collision.checkBallBallCollision(Balls[0], Balls[1], ECollisionType::ball))
		{
			
		}
		Balls[0].UpdatePos(deltaTime);
		Balls[1].UpdatePos(deltaTime);
	}
	
}

initializer::~initializer()
{
}
