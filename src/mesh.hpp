#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "shader.h"
#include "texture.hpp"

class Mesh
{
	public:
		Mesh(const char * path);
		~Mesh();
		void set_texture(const char *);
		void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
		std::vector<glm::vec3> getVertices();
	private:
		bool load(
				const char * path,
				std::vector<unsigned short> & indices,
				std::vector<glm::vec3> & vertices,
				std::vector<glm::vec2> & uvs,
				std::vector<glm::vec3> & normals
				);

		void loadShader(const char * , const char *);

		std::vector<short unsigned int> indices;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;

		GLuint vertexBuffer;
		GLuint uvBuffer;

		Texture * texture;
		Shader * shader;
};

#endif
