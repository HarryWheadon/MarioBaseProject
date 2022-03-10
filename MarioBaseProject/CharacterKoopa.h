#pragma once
#include "Character.h"

class CharacterKoopa : Character
{
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;

	/*void FlipRightWayUp();
	virtual void Render();
	virtual void Update();*/

public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	void TakeDamage();
	/*void Jump();*/
};

