#include "pch.h"
#include "Collision.h"
#include "../Initializer/initializer.h"

std::vector<std::shared_ptr<Collision>> Collision::AllCollision;

Collision::Collision(glm::vec3 position, glm::vec3 scale, glm::vec3 offset, ECollisionType collision_type) : scale(scale), offset(offset), collisionType(collision_type)
{
    min = position;
    max = position + scale;
    max.z = position.z - scale.z;

    AllCollision.push_back(std::make_shared<Collision>(*this));
}

void Collision::UpdatePosition(glm::vec3 position)
{
    min = position;
    max = position + scale;
    max.z = position.z - scale.z;
}

bool Collision::checkBallBoxCollision(RollingBall* ball, Mesh* wall)
{
	if(wall->position.x < ball->position.x + ball->size.x && ball->position.x - ball->size.x < wall->position.x + wall->size.x 
        && wall->position.y < ball->position.y + ball->size.y && ball->position.y - ball->size.y < wall->position.y + wall->size.y &&
        wall->position.z < ball->position.z + ball->size.z && ball->position.z - ball->size.z < wall->position.z + wall->size.z)
    {
	    if (HasOverlapped)
	    {
			std::cout << "Collision detected" << std::endl; 
	    }
	return true;
	}
}

bool Collision::checkBallBallCollision(RollingBall* ball1, RollingBall* ball2)
{
	float totalr = glm::length(ball1->GetPosition() + ball2->GetPosition());
	float d = totalr - (ball1->GetScale().x + ball2->GetScale().x);
	if (totalr <= d)
	{
     if (HasOverlapped)
	    {
			std::cout << "Collision detected" << std::endl; 
	    }
		return true;
	}
   
}

void Collision::DetectCollision(RollingBall b1, RollingBall b2)
{
    auto P0 = b1.position - b1.velocity;
    auto Q0 =  b2.position - b2.velocity;
    auto A = P0 - Q0;
    auto B = b1.position - b2.position;
    float AB = glm::dot(A, B);
}
