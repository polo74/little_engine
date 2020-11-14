#include "window.hpp"

double Window::ellapsedTime = 0;
int Window::width = 800;
int Window::height = 600;

Window::Window():
	/**
	 * Crée une fenetre  avec la librarie GLFW
	 */
	lastTime(0)
{
	// Set the error callback
	glfwSetErrorCallback(this->ErrorCallback);

	// Init GLFW
        if (!glfwInit())
                fprintf(stderr, "%s\n", "ATTENTION : erreur d'initialisation de GLFW");

	GLFWmonitor * monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	width = mode->width;
	height = mode->height;

        window = glfwCreateWindow(width, height, "Hello World", glfwGetPrimaryMonitor(), NULL);
        if (!window)
        {
                glfwTerminate();
                fprintf(stderr, "%s\n", "ATTENTION : Erreur de créatin de la fenetre GLFW");
        }

        glfwMakeContextCurrent(window);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::update()
{
	glfwSwapBuffers(window);

	double now = glfwGetTime();
	ellapsedTime = now - lastTime;
	lastTime = now;
}

Window::~Window()
{
	glfwTerminate();
}

GLFWwindow * Window::getWindow(void)
{
	return window;
}

double Window::getEllapsedTime()
{
	return ellapsedTime;
}

int Window::getWidth()
{
	return width;
}

int Window::getHeight()
{
	return height;
}

// Private

void Window::ErrorCallback(int, const char * err)
{
	fprintf(stdout, "GLFW error : %s\n", err);
}
