#include "Character.h"
#include "Texture2D.h"
#include "constants.h"

void Character::Jump()
{
	if (!m_jumping)
	{
		m_current_frame = 2;
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}

void Character::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= deltaTime * MOVEMENTSPEED;
}

void Character::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += deltaTime * MOVEMENTSPEED;
}

void Character::AddGravity(float deltaTime)
{
	if ((m_position.y + 64) <= (SCREEN_HEIGHT))
	{
		m_position.y += GRAVITY * deltaTime;
	}
	else
	{
		m_can_jump = true;
	}
}

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map)
{
	m_collision_radius = 15.0f;
	m_current_level_map = map;
	m_renderer = renderer;
	m_position = startPosition;
	m_alive = true;

	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load Character texture!" << std::endl;
	}

	m_moving_left = false;
		m_moving_right = false;
}


Character::~Character()
{
	m_renderer = nullptr;
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}

void Character::Render()
{
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();

	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame,0,m_single_sprite_w, m_single_sprite_h };

	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{

	//deal with jumping first
	if (m_jumping)
	{
		//adjust position
		m_position.y -= m_jump_force * deltaTime;

		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		//is jump force 0?
		if (m_jump_force <= 0.0f)
			m_jumping = false;
	}

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	if (m_moving_right)
	{
		MoveRight(deltaTime);
	}
	//collision position variables
	int centralX_position = (int)(m_position.x + (m_single_sprite_w * m_current_frame) *0.5) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;

	//deal with gravity
	if(m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{ 
	AddGravity(deltaTime);
	}
	else
	{
		//collided with ground so we can jump again
		m_can_jump = true;
	}

	if (GetHitWall() == true)
	{
		if (m_position.x < 0)
		{
			m_position.x += 1;
		}
		else if (m_position.x > 495)
		{
			m_position.x -= 1;
		}
	}
};

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}

void Character::SetAlive(bool isAlive)
{
	m_alive = isAlive;
}

void Character::HitWall(bool Hitwall)
{
	hitwall = Hitwall;
}


CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startposition, LevelMap* map) : Character(renderer, imagePath, startposition, map){}

void CharacterLuigi::LuigiUpdate(float deltaTime, SDL_Event e)
{

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = true;
			m_current_frame = 1;
			break;
		case SDLK_d:
			m_moving_right = true;
			m_current_frame = 1;
			break;
		case SDLK_SPACE:
			if (m_can_jump)
			{
				Jump();
				m_current_frame = 2;
			}
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = false;
			// changes the frame back to idle
			m_current_frame = 0;
			break;
		case SDLK_d:
			m_moving_right = false;
			// changes the frame back to idle
			m_current_frame = 0;
			break;
		}
		break;
	}
	Character::Update(deltaTime, e);
}

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startposition, LevelMap* map) : Character(renderer, imagePath, startposition, map){}

void CharacterMario::MarioUpdate(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_current_frame = 1;
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			m_current_frame = 1;
			m_moving_right = true;
			break;
		case SDLK_RSHIFT:
			if (m_can_jump)
			{
				Jump();
				m_current_frame = 2;
			}
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:

			m_moving_left = false;
			// changes the frame back to idle
			m_current_frame = 0;
			break;
		case SDLK_RIGHT:

			m_moving_right = false;
			// changes the frame back to idle
			m_current_frame = 0;
			break;
		}
		break;
	}
	Character::Update(deltaTime,e);
}

