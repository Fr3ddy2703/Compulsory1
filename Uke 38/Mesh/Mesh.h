#pragma once
#include "../Collision/Collision.h"

enum class ECollisionType;

struct Vertex
{
	glm::vec3 position = glm::vec3(0.f);
	glm::vec3 Color = glm::vec3(0.f);
	glm::vec3 normal = glm::vec3(0.f);
	Vertex(glm::vec3 position, glm::vec3 rgb) : position(position), Color(rgb)
	{
	}
};

struct Triangle
{
	Triangle(unsigned int indice1, unsigned int indice2, unsigned int indice3): index1(indice1), index2(indice2), index3(indice3){}
	unsigned int index1, index2, index3;
};

class RollingBall
{
public:
	std::vector<Vertex> bVertices;
	std::vector<Triangle> bIndices;
	glm::vec3 position = glm::vec3(0.f);
	glm::vec3 size = glm::vec3(1.f);
	float m = 0.f;
	glm::vec3 color = Color::Gold;
	glm::vec3 velocity = glm::vec3(1.f, 0.f, 0.f);

	glm::vec3& GetPosition() { return position; }
	glm::vec3& GetScale() { return size; }

	Collision Collider;

	void CreateSphere(glm::vec3 size, float segment, glm::vec3 pos, float mass,glm::vec3 speed, glm::vec3 color);
	void SubDivide(int index1, int index2, int index3, int n);

	void BindBuffer();

	void DrawSphere();

	void UpdatePos(float dt);

	void AddCollider(glm::vec3 scale,ECollisionType collisionType, glm::vec3 offset = glm::vec3(0.f));

private:
	unsigned int VBO;
	unsigned int EBO;
	unsigned int VAO;

};


class Mesh
{
public:
	std::vector<Vertex> mVertices;
	std::vector<Triangle> mIndices;
	glm::vec3 position = glm::vec3(1);
	glm::vec3 size = glm::vec3(1);


	Collision Collider;
	glm::vec3& GetPosition() { return position; }
	glm::vec3& GetScale() { return size; }
	
	void Draw();
	//void DrawBoundingBox(unsigned int shaderProgram);
	void CreateCube(glm::vec3 size, glm::vec3 pos, glm::vec3 color);
	void AddCollider(glm::vec3 scale,ECollisionType collisionType, glm::vec3 offset = glm::vec3(0.f));

	void BindBuffer();

	

private:
	unsigned int VBO;
	unsigned int EBO;
	unsigned int VAO;

};