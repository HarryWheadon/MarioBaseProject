#include "SoundEffect.h"

SoundEffect::SoundEffect(string path)
{
	LoadMusic(path);
}

SoundEffect::~SoundEffect()
{
}

void SoundEffect::Play(Mix_Music* music)
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(music, -1);
	}
}

void SoundEffect::LoadMusic(string path)
{
	Mix_Music* m_music = Mix_LoadMUS(path.c_str());
	if (m_music == nullptr)
	{
		cout << "Failed to load music. Error: " << Mix_GetError() << endl;
	}
	Play(m_music);
}
