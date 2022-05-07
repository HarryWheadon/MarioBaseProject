#include "GameScreenLevel1.h"
#include <iostream>

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					                   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					                   { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					                   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
					                   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					                   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++)
		{
			//do the update
			m_coins[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_coins[i]->GetPosition().y > 300.0f || m_coins[i]->GetPosition().y <= 64.0f) && (m_coins[i]->
				GetPosition().x < 64.0f || m_coins[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_coins[i], Mario_character))
					m_coins[i]->SetAlive(false);
	
				if (Collisions::Instance()->Circle(m_coins[i], Luigi_character))
					m_coins[i]->SetAlive(false);
			}
			//if the coin is no longer alive then schedule it for deletion
			if (!m_coins[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove coins -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	Koopa_character = new CharacterKoopa(m_renderer, "Images/koopa.png", m_level_map, position, direction, speed);
	m_enemies.push_back(Koopa_character);
}

void GameScreenLevel1::CreateCoin(Vector2D position, FACING direction, float speed)
{
	Coin_character = new CharacterCoin(m_renderer, "Images/coin.png", m_level_map, position, direction, speed);
	m_coins.push_back(Coin_character);
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[
					i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
					m_enemies[i]->SetAlive(false);
			}

			m_enemies[i]->HitWall(false);
			if ( m_enemies[i]->GetPosition().x < 0 || m_enemies[i]->GetPosition().x > 450)
				m_enemies[i]->HitWall(true);

			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->
				GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f)) {
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], Mario_character))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
						CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
						CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
					}
				}
				if (Collisions::Instance()->Circle(m_enemies[i], Luigi_character))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
				}
			}
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}


bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();

	Background_music = new SoundEffect;
	Background_music->LoadMusic("Music/Mario.mp3");

	//Instantiates a new Koopa to the enemies Array
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	//Instantiates a new coin to the coins Array
	// Top Left Coins
	CreateCoin(Vector2D(165, 40), FACING_RIGHT, COIN_SPEED);
	CreateCoin(Vector2D(135, 40), FACING_RIGHT, COIN_SPEED);
	CreateCoin(Vector2D(100, 40), FACING_RIGHT, COIN_SPEED);
	// Top Middle Coins
	CreateCoin(Vector2D(325, 40), FACING_RIGHT, COIN_SPEED);
	CreateCoin(Vector2D(360, 40), FACING_LEFT, COIN_SPEED);
	CreateCoin(Vector2D(390, 40), FACING_RIGHT, COIN_SPEED);
	// Top Middle Coins
	CreateCoin(Vector2D(675, 40), FACING_RIGHT, COIN_SPEED);
	CreateCoin(Vector2D(645, 40), FACING_RIGHT, COIN_SPEED);
	CreateCoin(Vector2D(610, 40), FACING_RIGHT, COIN_SPEED);
	// Top Right Coins
	CreateCoin(Vector2D(835, 40), FACING_RIGHT, COIN_SPEED);
	CreateCoin(Vector2D(870, 40), FACING_LEFT, COIN_SPEED);
	CreateCoin(Vector2D(900, 40), FACING_RIGHT, COIN_SPEED);


	//set up player character
	Mario_character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	Luigi_character = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);


	// Middle Left Coins
	/*CreateCoin(Vector2D(225, 135), FACING_RIGHT, COIN_SPEED);
	CreateCoin(Vector2D(260, 135), FACING_LEFT, COIN_SPEED);*/
	// Middle Right Coins
	//CreateCoin(Vector2D(740, 135), FACING_RIGHT, COIN_SPEED);
	//CreateCoin(Vector2D(775, 135), FACING_LEFT, COIN_SPEED);
	// Bottom Left Coins
	//CreateCoin(Vector2D(70, 265), FACING_RIGHT, COIN_SPEED);
	//CreateCoin(Vector2D(40, 265), FACING_RIGHT, COIN_SPEED);
	//CreateCoin(Vector2D(10, 265), FACING_RIGHT, COIN_SPEED);
	// Bottom Middle Coins
	//CreateCoin(Vector2D(550, 265), FACING_RIGHT, COIN_SPEED);
	//CreateCoin(Vector2D(520, 265), FACING_RIGHT, COIN_SPEED);
	//CreateCoin(Vector2D(490, 265), FACING_RIGHT, COIN_SPEED);
	//CreateCoin(Vector2D(460, 265), FACING_RIGHT, COIN_SPEED);

	//CreateCoin(Vector2D(1000, 265), FACING_RIGHT, COIN_SPEED);
	//CreateCoin(Vector2D(970, 265), FACING_RIGHT, COIN_SPEED);
	//CreateCoin(Vector2D(940, 265), FACING_RIGHT, COIN_SPEED);

	//load powblock
	m_pow_block = new PowBlock(m_renderer, m_level_map, Vector2D(240, 260));
	m_pow_block1 = new PowBlock(m_renderer, m_level_map, Vector2D(280, 260));
	m_screenshake = false;
	m_background_yPos = 0.0f;
	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/BackgroundMBLong.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	return true;
}

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	m_level_map = nullptr;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete Mario_character;
	Mario_character = nullptr;

	delete Luigi_character;
	Luigi_character = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

	m_coins.clear();

	m_enemies.clear();
}

void GameScreenLevel1::Render()
{

	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos),camera, SDL_FLIP_NONE, 0.0);

	//draw the enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}
	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}

	Mario_character->Render(camera);
	Luigi_character->Render(camera);
	m_pow_block->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	// do if the screen shake if required
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}
	//update Character
	Mario_character->MarioUpdate(deltaTime, e);
	Luigi_character->LuigiUpdate(deltaTime, e);
	UpdateCoins(deltaTime, e);
	UpdateEnemies(deltaTime, e);
	UpdatePOWBlock();
	
	camera.x = (Mario_character->GetPosition().x) - (SCREEN_WIDTH / 2);
	camera.w = SCREEN_WIDTH;
		camera.h = SCREEN_HEIGHT;
	if (camera.x < 0)
		camera.x = 0;
	if (camera.x > MAP_WIDTH - camera.w)
		camera.x = MAP_WIDTH - camera.w;
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
					DoScreenShake();
				m_pow_block->TakeHit();
				Mario_character->CancelJump();
			}
		}
	}

	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), Luigi_character->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			//collided while jumping
			if (Luigi_character->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				Luigi_character->CancelJump();
			}
		}
	}
}