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

bool Collision::checkBallBoxCollision(RollingBall ball, Mesh wall, ECollisionType ballType, ECollisionType wallType)
{
    if (ballType == ECollisionType::ball && wallType == ECollisionType::Boxes)
    {
        if (((wall.position.x <= ball.position.x + ball.size.x) && 
             (wall.position.x >= ball.position.x - ball.size.x)) ||
            ((wall.position.z - wall.size.z <= ball.position.z + ball.size.z) && 
             (wall.position.z >= ball.position.z - ball.size.z)))
        {
            //std::cout << "Collision detected" << "\n"; 
            return true; 
        }
    }
    return false;
}

bool Collision::checkBallBallCollision(RollingBall& ball1, RollingBall& ball2, ECollisionType type)
{
	float totalr = std::sqrtf(std::powf(ball1.position.x - ball2.position.x, 2.f) +  std::powf(ball1.position.y - ball2.position.y, 2.f) + std::powf(ball1.position.z + ball2.position.z, 2.f));
	float d = (ball1.GetScale().x + ball2.GetScale().x);
    glm::vec3 ClampedNormal = glm::vec3(0.f);
	if (type == ECollisionType::ball)
	{
		if(totalr > d)
            return false;
			std::cout << "Collision detected" << std::endl;
		auto P0 = ball1.position;
        auto Q0 = ball2.position;
		ClampedNormal = P0 - Q0;
		ball1.velocity = ball1.velocity - (2 * ball2.m) / (ball1.m + ball2.m) * glm::dot(ball1.velocity - ball2.velocity, ClampedNormal) /( glm::distance(P0, Q0) * glm::distance(P0, Q0)) * ClampedNormal;
		ball2.velocity = ball2.velocity - (2 * ball1.m) / (ball1.m + ball2.m) * glm::dot(ball2.velocity - ball1.velocity, Q0 - P0) /( glm::distance(Q0, P0) * glm::distance(Q0, P0)) * (Q0-P0);
			return true;
	}
	return false;
}

void Collision::ballphysics(RollingBall& b1, RollingBall& b2)
{
 
}