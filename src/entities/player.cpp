#include "player.hpp"

Player::Player(Body * body):
	AnimatedEntity(NULL, body)
{}

void Player::update()
{
	glm::mat4 transform = this->getBody()->getTransform();

	glm::vec3 scale;
        glm::quat rotation;
        glm::vec3 position;
        glm::vec3 skew;
        glm::vec4 perspective;

        glm::decompose(transform, scale, rotation, position, skew, perspective);


	fprintf(stdout, "position : %f", position.x);
}
