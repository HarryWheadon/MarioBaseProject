#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "LevelMap.h"
#include "PowBlock.h"

class Character;
class Texture2D;
class PowBlock;
class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	CharacterMario* Mario_character;
	CharacterLuigi* Luigi_character;
PowBlock* m_pow_block;
	void SetLevelMap();

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

