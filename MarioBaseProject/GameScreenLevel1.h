#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include <vector>

class Character;
class CharacterKoopa;
class CharacterCoin;
class Texture2D;
class PowBlock;
class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	CharacterMario* Mario_character;
	CharacterLuigi* Luigi_character;
	CharacterKoopa* Koopa_character;
	CharacterCoin* Coin_character;
	vector<CharacterKoopa*> m_enemies;
	vector<CharacterCoin*> m_coins;
	PowBlock* m_pow_block;
	SDL_Rect camera;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	void DoScreenShake();
	void SetLevelMap();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position, FACING direction, float speed);

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();
private:
	bool SetUpLevel();
	LevelMap* m_level_map;
};