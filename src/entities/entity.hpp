#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "mesh.hpp"
#include "physics.hpp"
#include "body.hpp"
#include "sound.hpp"
#include "entities.hpp"

#include "btBulletDynamicsCommon.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <vector>
#include "keys.hpp"
#include <math.h>
#include <iostream>

#include "camera.hpp"

class Entities;

class Entity
/**
 * The base of an entity : 
 * - a mesh to draw the entity
 * - a body to gerate the physics of the entity
 */
{
	public:
		Entity(Mesh * mesh, Body * body);
		virtual ~Entity();

		Mesh * getMesh(void);
		Body * getBody(void);

		void update();

		friend class Camera;
	protected:
		void destruct(Entities * entities);

		Body * body;
		Mesh * mesh;
};

#endif
