#include "debug.hpp"

Debug::Debug():
	debugMode (DBG_MAX_DEBUG_DRAW_MODE)
{
	loadShader("shaders/couleur3D.vert", "shaders/couleur3D.frag");
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &colorBuffer);
}

void Debug::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color)
{
	colors.push_back(glm::vec3(color[0], color[1], color[2]));
	lines.push_back(glm::vec3(from[0], from[1], from[2]));
	colors.push_back(glm::vec3(color[0], color[1], color[2]));
	lines.push_back(glm::vec3(to[0], to[1], to[2]));
}

void Debug::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & fromColor, const btVector3 & toColor)
{
	colors.push_back(glm::vec3(fromColor[0], fromColor[1], fromColor[2]));
	lines.push_back(glm::vec3(from[0], from[1], from[2]));
	colors.push_back(glm::vec3(toColor[0], toColor[1], toColor[2]));
	lines.push_back(glm::vec3(to[0], to[1], to[2]));
}

void Debug::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color){
	//TODO
	colors.push_back(glm::vec3(color[0], color[1], color[2]));
        lines.push_back(glm::vec3(PointOnB[0], PointOnB[1], PointOnB[2]));
        colors.push_back(glm::vec3(color[0], color[1], color[2]));
	btVector3 PointOnA = (PointOnB + normalOnB) * distance;
        lines.push_back(glm::vec3(PointOnA[0], PointOnA[1], PointOnA[2]));
}
void Debug::reportErrorWarning(const char* warningString){
	fprintf(stderr, "%s\n", warningString);
}
void Debug::draw3dText(const btVector3& location, const char* textString){}
void Debug::setDebugMode(int debugMode)
{
	this->debugMode = debugMode;
}
int Debug::getDebugMode()const
{
	return this->debugMode;
}

void Debug::clearLines()
{
	lines.clear();
	colors.clear();
}

void Debug::draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	glUseProgram(this->shader->getProgramID());
        glUniformMatrix4fv(glGetUniformLocation(this->shader->getProgramID(), "model"), 1, GL_FALSE, value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(this->shader->getProgramID(), "view"), 1, GL_FALSE, value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(this->shader->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(glm::vec3), &(lines[0]), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &(colors[0]), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_LINES, 0, lines.size());

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
        glUseProgram(0);
}

void Debug::loadShader(const char * vert, const char * frag)
{
        this->shader = new Shader(vert, frag);
        this->shader->charger();
}

