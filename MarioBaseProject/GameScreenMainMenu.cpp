#include "GameScreenMainMenu.h"

GameScreenMainMenu::GameScreenMainMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	setupLevel();

}
GameScreenMainMenu::~GameScreenMainMenu()
{
}

void GameScreenMainMenu::setupLevel()
{
	m_pointer = new Texture2D(m_renderer);
	m_pointer->LoadFromFile("Images/pointer.png");
	pointerYpos = 195;

	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/MainMenu.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}
}

void GameScreenMainMenu::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(0, 0), SDL_FLIP_NONE, 0.0);
	//Draws pointer
	m_pointer->Render(Vector2D(150, pointerYpos), SDL_FLIP_NONE, 0.0);
}

void GameScreenMainMenu::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: {
			pointerYpos = 195;
		}
		}

		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_DOWN: {
				pointerYpos = 240;
			}
			}
		}
	}
}

