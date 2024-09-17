#include "pch.h"
#include "Mesh.h"
#include "../Shaders/Shader.h"

void Mesh::CreateCube(glm::vec3 size, glm::vec3 pos, glm::vec3 color)
{
    GetPosition() = pos;
    GetScale() = size;

    Vertex v0{glm::vec3(0.f, 0.f, 0.f), color}; /* Front-Bot-left */
    Vertex v1{glm::vec3(1.f, 0.f, 0.f), color}; /* Front-Bot-right */
    Vertex v2{glm::vec3(1.f, 1.f, 0.f), color}; /* Front-Top-right */
    Vertex v3{glm::vec3(0.f, 1.f, 0.f), color}; /* Front-Top-left */
    Vertex v4{glm::vec3(0.f, 0.f, -1.f), color}; /* Back-Bot-left */
    Vertex v5{glm::vec3(1.f, 0.f, -1.f), color}; /* Back-Bot-right */
    Vertex v6{glm::vec3(1.f, 1.f, -1.f), color}; /* Back-Top-right */
    Vertex v7{glm::vec3(0.f, 1.f, -1.f), color}; /* Back-Top-left */

    mVertices.emplace_back(v0);
    mVertices.emplace_back(v1);
    mVertices.emplace_back(v2);
    mVertices.emplace_back(v3);
    mVertices.emplace_back(v4);
    mVertices.emplace_back(v5);
    mVertices.emplace_back(v6);
    mVertices.emplace_back(v7);

    /* Front */
    mIndices.emplace_back(0, 1, 2);
    mIndices.emplace_back(2, 3, 0);

    /* Right */
    mIndices.emplace_back(1, 5, 6);
    mIndices.emplace_back(6, 2, 1);

    /* Left */
    mIndices.emplace_back(0, 3, 7);
    mIndices.emplace_back(7, 4, 0);

    /* Back */
    mIndices.emplace_back(4, 7, 6);
    mIndices.emplace_back(6, 5, 4);

    /* Top */
    mIndices.emplace_back(3, 2, 6);
    mIndices.emplace_back(6, 7, 3);

    /* Bottom */
    mIndices.emplace_back(0, 4, 5);
    mIndices.emplace_back(5, 1, 0);

    for (auto element : mIndices)
    {
        glm::vec3 normal = glm::cross(mVertices[element.index2].position - mVertices[element.index1].position,
                                      mVertices[element.index3].position - mVertices[element.index1].position);
        mVertices[element.index1].normal += glm::normalize(normal);
        mVertices[element.index2].normal += glm::normalize(normal);
        mVertices[element.index3].normal += glm::normalize(normal);
    }

    BindBuffer();
}

void RollingBall::CreateSphere(glm::vec3 size, float segment, glm::vec3 pos, float mass,glm::vec3 speed, glm::vec3 color)
{
    GetScale() = size;
    GetPosition() = pos;
	velocity = speed;
    m = mass;

    Vertex v0 {glm::vec3(0.f, 0.f, 1.f), color};
    Vertex v1 {glm::vec3(1.f, 0.f, 0.f), color};
    Vertex v2 {glm::vec3(0.f, 1.f, 0.f), color};
    Vertex v3 {glm::vec3(-1.f, 0.f, 0.f), color};
    Vertex v4 {glm::vec3(0.f, -1.f, 0.f), color};
    Vertex v5 {glm::vec3(0.f, 0.f, -1.f), color};

	bVertices.emplace_back(v0);
    bVertices.emplace_back(v1);
    bVertices.emplace_back(v2);
    bVertices.emplace_back(v3);
    bVertices.emplace_back(v4);
    bVertices.emplace_back(v5);

    SubDivide(0, 1, 2, segment);
    SubDivide(0, 2, 3, segment);
    SubDivide(0, 3, 4, segment);
    SubDivide(0, 4, 1, segment);
    SubDivide(5, 2, 1, segment);
    SubDivide(5, 3, 2, segment);
    SubDivide(5, 4, 3, segment);
    SubDivide(5, 1, 4, segment);


	for (auto element : bIndices)
    {
		glm::vec3 normal = glm::cross(bVertices[element.index2].position - bVertices[element.index1].position,
                                      bVertices[element.index3].position - bVertices[element.index1].position);
        bVertices[element.index1].normal += glm::normalize(normal);
        bVertices[element.index2].normal += glm::normalize(normal);
        bVertices[element.index3].normal += glm::normalize(normal);
    }

	BindBuffer();
}

void Mesh::AddCollider(glm::vec3 scale, ECollisionType collisionType, glm::vec3 offset)
{
    	Collider = Collision(GetPosition()+offset, scale, offset, collisionType);
}

void RollingBall::SubDivide(int index1, int index2, int index3, int n)
{
	if (n > 0)
	{
		glm::vec3 v1 = bVertices[index1].position + bVertices[index2].position;
		v1 = glm::normalize(v1);
        glm::vec3 v2 = bVertices[index1].position + bVertices[index3].position;
        v2 = glm::normalize(v2);
        glm::vec3 v3 = bVertices[index3].position + bVertices[index2].position;
        v3 = glm::normalize(v3);

        int index4 = bVertices.size();

		bVertices.emplace_back(v1, color);
		bVertices.emplace_back(v2, color);
		bVertices.emplace_back(v3, color);

		int index5 = index4 + 1;
        int index6 = index4 + 2;

        SubDivide(index1, index4, index5, n - 1);
        SubDivide(index3, index5, index6, n - 1);
        SubDivide(index2, index6, index4, n - 1);
        SubDivide(index6, index5, index4, n - 1);
	}
	else
	{
        int indice1 = bVertices.size();
		bVertices.emplace_back(glm::vec3{bVertices[index1].position}, color);
        int indice2 = bVertices.size();
		bVertices.emplace_back(glm::vec3{bVertices[index2].position}, color);
		int indice3 = bVertices.size();
		bVertices.emplace_back(glm::vec3{bVertices[index3].position}, color);

        bIndices.emplace_back(indice1, indice2, indice3);

	}
}

void RollingBall::BindBuffer()
{
        // VAO
    glGenBuffers(1, &VBO);

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, bVertices.size() * sizeof(Vertex), bVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bIndices.size()*sizeof(Triangle), bIndices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Color)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void RollingBall::DrawSphere()
{
	glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, position);
    model = glm::scale(model, size);
    glUniformMatrix4fv(glGetUniformLocation(Shader::ShaderProgram, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, bIndices.size()*3, GL_UNSIGNED_INT, (void*)(0 * sizeof(unsigned int)));
    glBindVertexArray(0);
}

void RollingBall::UpdatePos(float dt)
{
	position += velocity * dt;
	Collider.UpdatePosition(position);
}

void RollingBall::AddCollider(glm::vec3 scale, ECollisionType collisionType, glm::vec3 offset)
{
	Collider = Collision(GetPosition()+offset, scale, offset, collisionType);
}



void Mesh::BindBuffer()
{
    // VAO
    glGenBuffers(1, &VBO);

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size()*sizeof(Triangle), mIndices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Color)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


float calculateNormal(glm::vec3&& vector1, glm::vec3&& vector2) {
    return vector1[0]* vector2[2]- vector2[0]*vector1[2];
}

void Mesh::Draw()
{
    glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, position);
    model = glm::scale(model, size);
    glUniformMatrix4fv(glGetUniformLocation(Shader::ShaderProgram, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, mIndices.size()*3, GL_UNSIGNED_INT, (void*)(0 * sizeof(unsigned int)));
    glBindVertexArray(0);
}
