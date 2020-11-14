#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <vector>
#include "entity.hpp"

class Entity;

class Entities
{
	public:
		Entities();

		void add(Entity * entity);
		void remove(Entity * entity);
		void remove(int indice);

		std::vector<Entity *> * getEntities();

		void update();
	private:
		std::vector<Entity *> entities;
};

#endif
