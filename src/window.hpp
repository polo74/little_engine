#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>

#include "window.hpp"

#include <iostream>

class Window
{
	public:
		Window();
		~Window();
		GLFWwindow * getWindow(void);
		void update();
		static double getEllapsedTime();
		static int getWidth();
		static int getHeight();

	private:
		static void ErrorCallback(int, const char *);

		GLFWwindow * window;

		static double ellapsedTime;
		double lastTime;

		static int width;
		static int height;
};

#endif
