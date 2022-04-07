#pragma once
#include <SDL.h>
#include <iostream>
using namespace std;

class SoundEffect
{
public:
	SoundEffect();
	~SoundEffect();
	void Play(string path);
};

