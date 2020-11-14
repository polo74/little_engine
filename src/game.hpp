#ifndef GAME_HPP
#define GAME_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "entities.hpp"
#include "body.hpp"
#include "player.hpp"
#include "camera.hpp"
#include "display.hpp"
#include "window.hpp"
#include "keys.hpp"
#include "physics.hpp"
#include "camera.hpp"
#include "debug.hpp"
#include "gui.hpp"
#include "osm.hpp"

#include "sound.hpp"

#include <iostream>

//#include <vector>

int game(int, char **);
btRigidBody * drop(glm::vec3, glm::vec3);

#endif
