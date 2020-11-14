#include "animated_entity.hpp"

AnimatedEntity::AnimatedEntity(Mesh * mesh, Body * body):
	Entity(mesh, body)
{}

void AnimatedEntity::move(glm::vec3 direction)
	/**
	 * update the entity position and move it to the position `initial position + direction`
	 */
{
	glm::mat4 initial = this->body->getTransform();
	glm::mat4 translate = glm::translate(direction);
	initial = initial * translate;
	this->body->setTransform(initial);
}

void AnimatedEntity::rotate(glm::vec3 ypr)
	/**
	 * update the entity rotation `initial rotation + rotaion`
	 */
{
	glm::mat4 initial = this->body->getTransform();

	glm::mat4 rotate;

	rotate = glm::rotate(ypr.x, glm::vec3(1, 0, 0));
	initial = initial * rotate;

	rotate = glm::rotate(ypr.y, glm::vec3(0, 1, 0));
	initial = initial * rotate;

	rotate = glm::rotate(ypr.z, glm::vec3(0, 0, 1));
	initial = initial * rotate;

	this->body->setTransform(initial);
}
