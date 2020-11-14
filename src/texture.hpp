#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <stdio.h>
#include <string>
#include <cstring>


class Texture
{
	public:
		Texture();
		~Texture();

		GLuint getID();
		void load(const char *);
		void load(const void * data, int, int);
	private:

		GLuint textureID;
};

#endif
