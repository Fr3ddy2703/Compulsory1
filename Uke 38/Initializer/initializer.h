#pragma once
#include "../Camera/camera.h"
#include "../Mesh/Mesh.h"

class ElementBuffer;
class VertexBuffer;
struct GLFWwindow;

class initializer
{
public:
	GLFWwindow *window;
	static camera UseCamera;
	static float DeltaTime;
	RollingBall Sphere;
	Mesh Floor;
	Mesh Wall;
	Mesh Wall2;
	Mesh Wall3;
	Mesh Wall4;

	initializer(){};

	virtual void Initialize();
	virtual void Create();
	virtual void Run();
	virtual void Update(float deltaTime);

	virtual  ~initializer();

private:
	std::vector<Mesh> Meshes; 
	std::vector<RollingBall> Balls; 

};

