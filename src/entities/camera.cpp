#include "camera.hpp"

Camera::Camera(Entity * entity)
{
	this->entity = entity;
}

glm::mat4 Camera::view(void)
	/**
	 * return the view matrix
	 */
{
	glm::mat4 transform = this->entity->body->getTransform();

	glm::vec3 scale;
	glm::quat rotation; 
	glm::vec3 from; 
	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(transform, scale, rotation, from, skew, perspective);


	fprintf(stdout, "from : %f, %f, %f\n", from.x, from.y, from.z);

	glm::vec4 to = glm::vec4(from, 1.0f);
	glm::vec4 up = glm::vec4(from, 1.0f);

	{
	to = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * to;
	to = glm::vec4(from, 0.0f) + (glm::toMat4(rotation) * (to - glm::vec4(from, 0.0f)));
	}

	{
	up = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * up;
	up = (glm::toMat4(rotation) * (up - glm::vec4(from, 0.0f)));
	}

/*
	up = glm::toMat4(rotation) * up;
	up = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * up;

	to = glm::toMat4(rotation) * to;
	to = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * to;
*/
	fprintf(stdout, "up : %f, %f, %f\n", up.x, up.y, up.z);

	return glm::lookAt(from, glm::vec3(to.x, to.y, to.z), glm::vec3(up.x, up.y, up.z));
}

glm::mat4 Camera::projection(void)
	/**
	 * return the projection matrix
	 */
{
	return glm::perspective(70.0f, (2560.0f/1440.0f), .1f, 100000.0f);
}
