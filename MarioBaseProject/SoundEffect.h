#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
using namespace std;

class SoundEffect
{
public:
	SoundEffect(string path);
	~SoundEffect();
	void Play(Mix_Music* music);
	void LoadMusic(string path);
private:
};

