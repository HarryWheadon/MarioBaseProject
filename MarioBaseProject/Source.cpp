#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include "SoundEffect.h"
using namespace std;

//Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();

	//Update the screen
	SDL_RenderPresent(g_renderer);
}

bool InitSDL()
{

	//initialise the mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Mixer could not init. Error: " << Mix_GetError();
		return false;
	}
	 
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//setup passes so crate window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "window was not created. Error " << SDL_GetError();
			return false;
		}
	}

	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

	if (g_renderer != nullptr)
	{
		//init PNG loading
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags) & imageFlags))
		{
			cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
			return false;
		}
	}
	else
	{
		cout << "Renderer could not initialise. Error: " << SDL_GetError();
		return false;
	}

}

void CLoseSDL()
{
	//release the window
	g_window = nullptr;
	SDL_DestroyWindow(g_window);

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	//release the renderer
	g_renderer = nullptr;
	SDL_DestroyRenderer(g_renderer);

//destroy the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;
}

bool Update()
{
	Uint32 new_time = SDL_GetTicks();

	//Event handler
	SDL_Event e;

	//get events
	SDL_PollEvent(&e);

	//handle the events
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_x:{
			return true;
			break; }
		case SDLK_RETURN:
			game_screen_manager->ChangeScreen(SCREEN_LEVEL1);
		}
	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false;
}


int main(int argc, char* args[])
{
	if (InitSDL())
	{
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);
			//set the time
			g_old_time = SDL_GetTicks();

		//flag to check if we wish to quit
		bool quit = false;

		//Game Loop
		while(!quit)
		{
			Render();
			quit = Update();
		}
	}

	CLoseSDL();

	return 0;
}

