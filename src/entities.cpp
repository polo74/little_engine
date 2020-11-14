#include "entities.hpp"

Entities::Entities()
{
	fprintf(stdout, "constructor of Entities\n");
}

void Entities::add(Entity * entity)
{
	entities.push_back(entity);
	//fprintf (stdout, "add entity : %p at position %d\n", entity, entities.size());
}

void Entities::remove(Entity * entity)
{
	if (!entities.empty())
	{
		int indice = -1;
		for (int i = 0; i < entities.size(); i++)
		{
			if (entities[i] == entity){
				indice = i;
			}
		}

		if (indice >= 0)
		{
			entities.erase(entities.begin() + indice);
			delete entity;

		}
	}
}
void Entities::remove(int indice)
{
	delete entities[indice];
	entities.erase(entities.begin() + indice);
}

std::vector<Entity *> * Entities::getEntities()
{
	return &entities;
}

void Entities::update()
{
	for (int i = 0; i < entities.size(); i++)
	{
		(entities)[i]->update();
	}
}
