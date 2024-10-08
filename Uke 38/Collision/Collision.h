#pragma once
#define PrintBool(x) std::cout << ((x) ? "True" : "False") << "\n"

class RollingBall;
class Mesh;

enum class ECollisionType
{
    Boxes,
    ball
};

class Collision
{
public:
    glm::vec3 min = glm::vec3(0.f);
    glm::vec3 max= glm::vec3(0.f);
    glm::vec3 scale;
    glm::vec3 offset = glm::vec3(0.f);
    ECollisionType collisionType;

	Collision() = default;
    
    Collision(glm::vec3 position, glm::vec3 scale, glm::vec3 offset = glm::vec3(0.f),ECollisionType collision_type = ECollisionType::Boxes);
    void UpdatePosition(glm::vec3 position);
    bool checkBallBoxCollision(RollingBall ball, Mesh wall, ECollisionType ballType, ECollisionType wallType);
	bool checkBallBallCollision(RollingBall& ball1, RollingBall& ball2, ECollisionType type);
    void ballphysics(RollingBall& b1, RollingBall& b2);

private:
    static std::vector<std::shared_ptr<Collision>> AllCollision;
};
