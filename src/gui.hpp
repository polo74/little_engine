#ifndef GUI_HPP
#define GUI_HPP

#include "texture.hpp"
#include "shader.h"
#include "camera.hpp"
#include "characters.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

#include <map>

class Gui
{
	public:
		Gui();
		void drawText(glm::mat4, glm::mat4, glm::mat4, glm::vec3, const GLchar *);
		void drawBox(glm::mat4, glm::mat4, glm::mat4, glm::vec3);
	private:
		Shader * shader; 
		GLuint vertexBuffer;
		GLuint uvBuffer;

		Characters * characters;
};

#endif
