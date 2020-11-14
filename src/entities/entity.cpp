#include "entity.hpp"

using namespace glm;

Entity::Entity(Mesh * mesh, Body * body)
{
	this->mesh = mesh;
	this->body = body;
	
	if (this->body)
		this->body->setUserPointer(this);
}

Entity::~Entity()
{
	fprintf(stdout, "destructor of Entity\n");
	delete mesh;
	delete body;
}

Mesh * Entity::getMesh()
{
	if (mesh)
		return mesh;
	else
		return NULL;
}

Body * Entity::getBody()
{
	if (this->body)
		return this->body;
	else
		return NULL;
}

void Entity::update()
{}

void Entity::destruct(Entities * entities)
{
	entities->remove(this);
}

