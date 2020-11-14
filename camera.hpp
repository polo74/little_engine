#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "entity.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	public:
		Camera();

		static glm::mat4 view(glm::vec3 position, glm::vec3 direction);
		static glm::mat4 projection(double FOV, double ratio);
	private:
};

#endif
