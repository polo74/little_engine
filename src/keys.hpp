#ifndef KEYS_HPP
#define KEYS_HPP

#include "window.hpp"

class Keys
{
	public:
		Keys(GLFWwindow * window);
		void update(GLFWwindow * window);

		static bool forward;
		static bool rearward;
		static bool right;
		static bool left;
		static double look_right;
		static bool look_left;
		static double look_up;
		static bool look_down;
		static bool jump;
		static bool fire;
	private:
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void error_callback(int error, const char* description);

};

#endif
