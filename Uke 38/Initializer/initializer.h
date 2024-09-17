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
	std::vector<RollingBall> Balls;
	bool start = false;

private:
	std::vector<Mesh> Meshes; 


};

