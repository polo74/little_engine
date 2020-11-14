#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "entity.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity;

class Camera
/**
 * manage the camera
 */
{
	public:
		// Constructor
		Camera(Entity *);
		// Functions
		glm::mat4 view(void);
		glm::mat4 projection(void);
	private:
		// Classes
		Entity * entity;
};

#endif
