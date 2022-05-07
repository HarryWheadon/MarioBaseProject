#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include "Character.h"

class Texture2D;
class GameScreenMainMenu : GameScreen
{
private:
	Texture2D* m_background_texture;


public:
	GameScreenMainMenu(SDL_Renderer* renderer);
	~GameScreenMainMenu();

	void setupLevel();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

};

