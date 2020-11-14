#include "keys.hpp"

#include <thread>
#include <iostream>

bool Keys::forward = 0;
bool Keys::rearward = 0;
bool Keys::left = 0;
bool Keys::right = 0;
double Keys::look_right = 0;
bool Keys::look_left = 0;
double Keys::look_up = 0;
bool Keys::look_down = 0;
bool Keys::jump = 0;
bool Keys::fire = 0;

Keys::Keys(GLFWwindow * window)
{
	glfwSetErrorCallback(Keys::error_callback);
	glfwSetKeyCallback(window, Keys::key_callback);
}

void Keys::update(GLFWwindow * window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, 0, 0);
	look_right = xpos * Window::getEllapsedTime();
	look_up = ypos * Window::getEllapsedTime();
}

void Keys::error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void Keys::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		forward = true;
	}
	
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		rearward = true;
	}
	
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		right = true;
	}
	
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		left = true;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        {
                look_right = true;
        }


	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        {
                look_left = true;
        }

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        {
                look_up = true;
        }

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        {
                look_down = true;
        }

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        {
                jump = true;
        }

	if (key == GLFW_KEY_F && action == GLFW_PRESS)
        {
                fire = true;
        }

	// RELEASE

	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		forward = false;
	}

	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		rearward = false;
	}

	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		right = false;
	}

	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		left = false;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
        {
                look_right = false;
        }

        if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
        {
                look_left = false;
        }

	if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
        {
                look_up = true;
        }

	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
        {
                look_down = true;
        }

        if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
        {
                jump = false;
        }

	if (key == GLFW_KEY_F && action == GLFW_RELEASE)
        {
                fire = false;
        }

}

