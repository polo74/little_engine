#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include "texture.hpp"

#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

struct Character;

class Characters
{
	public:
		Characters();
		Character getCharacter(GLchar c);
		void draw(glm::mat4, glm::mat4, glm::mat4, glm::vec3, GLchar);
	private:
		std::map<GLchar, Character> characters;
		GLuint uvBuffer;
		Shader * shader;
		short int buffersize;
};

struct Character
{
	Texture * texture;    // Identificateur de la texture du glyphe
	glm::ivec2 size;          // Taille du glyphe
	glm::ivec2 bearing;    // Approche gauche et œil du glyphe
	glm::ivec2 advance;     // Empattement du glyphe
	GLuint vertexBuffer;
};

#endif
