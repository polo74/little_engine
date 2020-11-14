#ifndef ANIMATED_ENTITY_HPP
#define ANIMATED_ENTITY_HPP

#include "entity.hpp"

class AnimatedEntity : public Entity
{
	public:
		// Constructor
		AnimatedEntity(Mesh *, Body *);
		// Functions
		void move(glm::vec3);
		void rotate(glm::vec3);
};

#endif
