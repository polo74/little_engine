#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include "window.hpp"

/**
 * Dispaying class : initialize opengl, and so on...
 */

class Display
{
	/**
	 * TEST
	 * et retest
	 */
	public:
		Display();
		~Display();

		void clear();
		void draw(Window * window);
};

#endif
