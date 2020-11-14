#ifndef BODY_HPP
#define BODY_HPP

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "physics.hpp"
#include "btBulletDynamicsCommon.h"
#include "mesh.hpp"

class Body
{
	public :
		Body(Physics * physics, btRigidBody * body);
		~Body();

		void setUserPointer(void * pointer);
		void * getUserPointer();

		void setLinearVelocity(glm::vec3);

		glm::mat4 getModel();
		btTransform * getWorldTransform();
		glm::vec3 getLinearVelocity();

		void setScale(btVector3);

		glm::vec3 getPosition(void);
		void setPosition(glm::vec3);
		//Correct
		glm::mat4 getTransform(void);
		void setTransform(glm::mat4);
	private:
		void reload(btRigidBody::btRigidBodyConstructionInfo);

		Physics * physics;
		btRigidBody * body;
		btVector3 scale;
};

#endif
