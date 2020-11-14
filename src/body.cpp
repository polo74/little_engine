#include "body.hpp"

Body::Body(Physics * physics, btRigidBody * body):
	scale(btVector3(1, 1, 1))
{
	this->physics = physics;
	this->body = body;
	physics->addRigidBody(body);
	body->setUserPointer(NULL);
}

Body::~Body()
{
	physics->removeRigidBody(body);
	delete body;
}

void Body::setUserPointer(void * pointer)
{
	body->setUserPointer(pointer);
}

void * Body::getUserPointer()
{
	return body->getUserPointer();
}

void Body::setLinearVelocity(glm::vec3 velocity)
{
	body->setLinearVelocity(btVector3(
				velocity.x,
				velocity.y,
				velocity.z
				));
}

glm::mat4 Body::getModel()
{
	glm::mat4 model = glm::mat4(1.0);
	btTransform transform;
	body->getMotionState()->getWorldTransform(transform);
	transform.getOpenGLMatrix(glm::value_ptr(model));
	glm::mat4 res = model * glm::scale(glm::vec3(this->scale[0], this->scale[1], this->scale[2]));
	return res;
}

btTransform * Body::getWorldTransform()
{
	return &(body->getWorldTransform());
}

glm::vec3 Body::getLinearVelocity()
{
	btVector3 velocity = body->getLinearVelocity();
	return glm::vec3(
			velocity[0],
			velocity[1],
			velocity[2]
			);
}

void Body::setScale(btVector3 scale)
{
	btCollisionShape * collisionShape = body->getCollisionShape();
	collisionShape->setLocalScaling(btVector3(1/this->scale[0], 1/this->scale[1], 1/this->scale[2]));

	this->scale = scale;
	int mass = 1/body->getInvMass();
	btMotionState * motionState = body->getMotionState();
	btVector3 localInertia = body->getLocalInertia();

	collisionShape->setLocalScaling(this->scale);

	btRigidBody::btRigidBodyConstructionInfo info = btRigidBody::btRigidBodyConstructionInfo(mass, motionState, collisionShape, localInertia);
	reload(info);
}


void Body::reload(btRigidBody::btRigidBodyConstructionInfo info)
{
	this->body = new btRigidBody(info);
}


glm::vec3 Body::getPosition(void)
	/**
	 * return the object position
	 */
{
	btTransform transform = this->body->getCenterOfMassTransform();
	btVector3 bt_position = transform.getOrigin();
	glm::vec3 glm_position = glm::vec3(bt_position.getX(), bt_position.getY(), bt_position.getZ());
	return glm_position;
}

void Body::setPosition(glm::vec3 glm_position)
	/**
	 * define the object position
	 */
{
	btVector3 bt_position = btVector3(btScalar(glm_position.x), btScalar(glm_position.y), btScalar(glm_position.z));
	btTransform transform = this->body->getCenterOfMassTransform();
	transform.setOrigin(bt_position);
	this->body->setCenterOfMassTransform(transform);
	return;
}

//Correct

glm::mat4 Body::getTransform(void)
{
	glm::mat4 model;
	btTransform transform = this->body->getCenterOfMassTransform();
	transform.getOpenGLMatrix(glm::value_ptr(model));
	return model;
}

void Body::setTransform(glm::mat4 model)
{
	btTransform transform = this->body->getCenterOfMassTransform();
	transform.setFromOpenGLMatrix(glm::value_ptr(model));
	this->body->setCenterOfMassTransform(transform);
	return;
}
