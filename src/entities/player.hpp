#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "animated_entity.hpp"

class Player : public AnimatedEntity
{
	public:
		Player(Body *);
		void update();
	private:
};

#endif
