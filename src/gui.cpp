#include "gui.hpp"
#include "window.hpp"

Gui::Gui(){
	fprintf(stdout, "loadGui !\n");

	characters = new Characters();
	shader = new Shader("shaders/character2D.vert", "shaders/character2D.frag");
        shader->charger();
}

void Gui::draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 color, const GLchar * text)
{
	int i = 0;
	int x = 0, y = 0;
	GLchar c = text[i];

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
