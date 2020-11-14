#include "osm.hpp"
#include <iostream>

MapGen::MapGen(Entities * entities)
{
	this->entities = entities;
}

void MapGen::way(const osmium::Way & way)
{
	roads(way);
	buildings(way);
}

void MapGen::area(const osmium::Area & area)
{
}

void MapGen::roads(const osmium::Way & way)
{
	fprintf(stdout, "highway : %s\n", way.get_value_by_key("highway"));
}

void MapGen::buildings(const osmium::Way & way)
{
	const char * value = way.get_value_by_key("building");
	if (value != nullptr)
	{
		std::vector<osmium::NodeRef> nodes;
		for (osmium::NodeRef n : way.nodes())
		{
			nodes.push_back(n);
		}
	//m_buildings.push_back(nodes);
	}
}
