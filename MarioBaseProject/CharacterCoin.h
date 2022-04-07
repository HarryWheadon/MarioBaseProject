#pragma once
#include "Character.h"
#include "GameScreenLevel1.h"

class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterCoin();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_frame_delay;
	float m_current_frame;
};

