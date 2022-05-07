#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenMainmenu.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_current_screen = nullptr;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;

	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render()
{
	m_current_screen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_current_screen->Update(deltaTime, e);


	/*	SDL_PollEvent(&e);
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_t:
				ChangeScreen(SCREEN_LEVEL1);
			}
		}*/
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	//clear up the old Screen
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}

	if (new_screen == SCREEN_MENU)
	{
		GameScreenMainMenu* tempScreen;
		tempScreen = new GameScreenMainMenu(m_renderer);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
	}
	else if (new_screen == SCREEN_LEVEL1)
	{
		GameScreenLevel1* tempScreen1;
		tempScreen1 = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)tempScreen1;
		tempScreen1 = nullptr;
	}
	/*switch (new_screen)
	{
	case SCREEN_MENU:
	{
		GameScreenMainMenu* tempScreen;
		tempScreen = new GameScreenMainMenu(m_renderer);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
	}
	case SCREEN_LEVEL1:
	{
		GameScreenLevel1* tempScreen1;
		tempScreen1 = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)tempScreen1;
		tempScreen1 = nullptr;
	}
	}*/
}
