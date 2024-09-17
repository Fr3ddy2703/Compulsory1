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

	Sphere.CreateSphere(glm::vec3(1.f),4.f, glm::vec3(10.f, 10.f, 0.f), 1.f,glm::vec3(1.f, 0.f, 0.f),Color::Gold);
	Sphere.AddCollider(Sphere.GetScale(), ECollisionType::ball);

	/* Creating the balls */
	//for (int i = 0; i < 1; i++)
	//{
		RollingBall kule;
		kule.CreateSphere(glm::vec3(1.f),4.f, glm::vec3(20.f, 10.f, 0.f), 0.5f,glm::vec3(-1.f, 0.f, 0.f),Color::Gold);
		kule.AddCollider(kule.GetScale(), ECollisionType::ball);
		Balls.push_back(kule);
	//	
	//}

	Meshes.emplace_back(Floor);
	Meshes.emplace_back(Wall);
	Meshes.emplace_back(Wall2);
	Meshes.emplace_back(Wall3);
	Meshes.emplace_back(Wall4);
	Balls.emplace_back(Sphere);

}

void initializer::Run()
{
	Create();
	float FirstFrame = 0.0f;
	glm::vec3 color(Color::Grey);

	glEnable(GL_DEPTH_TEST);
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
			//std::cout << "Sphere position: " << sphere.GetPosition().x << " " << sphere.GetPosition().y << " " << sphere.GetPosition().z << std::endl;
		}
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

void initializer::Update(float deltaTime)
{
    for (auto& ball : Balls)
    {
        Collision collision;
    	ball.UpdatePos(deltaTime);
		Sphere.UpdatePos(deltaTime);
		 //if (
			// collision.checkBallBoxCollision(ball, Wall, ECollisionType::ball, ECollisionType::Boxes) ||
   //         collision.checkBallBoxCollision(ball, Wall2, ECollisionType::ball, ECollisionType::Boxes) ||
   //         collision.checkBallBoxCollision(ball, Wall3, ECollisionType::ball, ECollisionType::Boxes) ||
   //         collision.checkBallBoxCollision(ball, Wall4, ECollisionType::ball, ECollisionType::Boxes))
   //     {
			// ball.velocity = -ball.velocity;
		
   //     }
        if(collision.checkBallBallCollision(Sphere, ball, ECollisionType::ball))
		{
			//std::cout << "Ball ball collision detected" << std::endl;
        }
    
    }
	
}

initializer::~initializer()
{
}
