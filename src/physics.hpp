#ifndef PHYSICS_HPP
#define PHYSICS_HPP


#include <btBulletDynamicsCommon.h>
#include "BulletDynamics/MLCPSolvers/btDantzigSolver.h"
#include "BulletDynamics/MLCPSolvers/btSolveProjectedGaussSeidel.h"
#include "BulletDynamics/MLCPSolvers/btMLCPSolver.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Physics
{
	public:
		Physics();
		~Physics();

		void addRigidBody(btRigidBody * body);
		void removeRigidBody(btRigidBody * body);
		void addConstrain(btTypedConstraint * constrain);
		void removeConstrain(btTypedConstraint * constrain);
		void setDebug(btIDebugDraw * debug);
		void debugDraw();
		void update(float);
	private:
		btDiscreteDynamicsWorld * world;
};

#endif
