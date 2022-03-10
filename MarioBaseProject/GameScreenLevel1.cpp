#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "Collisions.h"
#include "PowBlock.h"

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);
}

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	m_level_map = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete Mario_character;
	Mario_character = nullptr;

	delete Luigi_character;
	Luigi_character = nullptr;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//update Character
	Mario_character->MarioUpdate(deltaTime, e);
	Luigi_character->LuigiUpdate(deltaTime, e);
	UpdatePOWBlock();
}

bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();

	//set up player character
	Mario_character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	Luigi_character = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);

	//load powblock
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	return true;
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	Mario_character->Render();
	Luigi_character->Render();
	m_pow_block->Render();
}

void GameScreenLevel1::UpdatePOWBlock()
{

	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), Mario_character->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			//collided while jumping
			if (Mario_character->IsJumping())
			{
				/*	DoScreenShake();*/
				m_pow_block->TakeHit();
				Mario_character->CancelJump();
			}
		}
	}
}