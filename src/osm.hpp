#include <osmium/handler.hpp>
#include <osmium/osm/node.hpp>
#include <osmium/osm/way.hpp>
#include <osmium/io/any_input.hpp>
#include <osmium/visitor.hpp>
#include <osmium/index/map/sparse_mem_array.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>
#include <osmium/osm/tag.hpp>

#include <btBulletDynamicsCommon.h>

#include "entities.hpp"

#include <iostream>
#include <vector>

typedef struct Building Building;

class MapGen : public osmium::handler::Handler
{
	public :
		MapGen(Entities * entities);

		void way(const osmium::Way &);
		void area(const osmium::Area &);
	private:
		void roads(const osmium::Way & way);
		void buildings(const osmium::Way & way);

		Entities * entities;
};
