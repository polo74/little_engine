#include "gui.hpp"
#include "window.hpp"

Gui::Gui(){
	fprintf(stdout, "loadGui !\n");

	characters = new Characters();
	shader = new Shader("shaders/character2D.vert", "shaders/character2D.frag");
}

void Gui::drawText(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 color, const GLchar * text)
{
	int i = 0;
	int x = 0, y = 0;
	GLchar c = text[i];

	fprintf(stdout, "draw text !\n");

	while(c != '\0')
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0), glm::vec3(x, y, 0.0f));
		model = model * translate;
		characters->draw(model, glm::mat4(1), projection, color, c);

		Character ch = characters->getCharacter(text[i]);

		x = (ch.advance.x >> 6);
		y = (ch.advance.y >> 6);

		i++;
		c = text[i];
	}
	fprintf(stdout, "\n");
}

void Gui::drawBox(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 color)
{

	Shader * shader = new Shader("shaders/couleur2D.vert", "shaders/couleur2D.frag");
	shader->charger();
/*
	for(int i = 0; i < 4; i++)
	{
		fprintf(stdout, "%f, %f, %f, %f\n", model[i][0], model[i][1], model[i][2], model[i][3]);
	}

	fprintf(stdout, "\n");
*/

	GLfloat vertices[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.0f,  0.5f

	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(shader->getProgramID());
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniform3f(glGetUniformLocation(shader->getProgramID(), "color"), color.x, color.y, color.z);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) * sizeof(float));

	glDisableVertexAttribArray(0);
	glUseProgram(0);
}
