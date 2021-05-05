#include "display.hpp"

Display::Display()
{
	//glewExperimental=GL_TRUE;
	GLenum err = glewInit();
	if (err == GLEW_OK)
	{
		fprintf(stdout, "initialisation de glew : OK\n");
	}
	else
	{
		fprintf(stderr, "Display Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
}

Display::~Display()
{
	glfwTerminate();
}

void Display::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::draw(Window * window)
{
	if (window)
	{
		window->update();
		glfwPollEvents();
	}
}
