#ifndef DEBUGDRAWER_HPP
#define DEBUGDRAWER_HPP

#include <btBulletDynamicsCommon.h>

#include <GL/glew.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

class Debug : public btIDebugDraw
{
	public:
		Debug();
		void drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color);
		void drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & fromColor, const btVector3 & toColor);
		virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
		virtual void reportErrorWarning(const char* warningString);
		virtual void draw3dText(const btVector3& location, const char* textString);
		virtual void setDebugMode(int debugMode);
		virtual int getDebugMode() const;

		virtual void clearLines();

		void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	private:
		void loadShader(const char * vert, const char * frag);

		int debugMode;

		std::vector <glm::vec3> lines;
		std::vector <glm::vec3> colors;

		GLuint vertexBuffer;
		GLuint colorBuffer;

		Shader * shader;
};

#endif
