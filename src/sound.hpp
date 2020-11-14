#ifndef SOUND_HPP
#define SOUND_HPP

#include <AL/al.h>
#include <AL/alc.h>

#include <assert.h>
#include <inttypes.h>
#include <limits.h>

#include <iostream>
#include <sndfile.h>
#include <vector>

class Sound
{
	public:
		Sound();
		~Sound();
		ALuint load(const char * filename);
		ALuint add_source();
		void play(ALuint, ALuint);
	private :
};

#endif
