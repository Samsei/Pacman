#include "SDL.h"
#include "assert.h"
#include "pacman.h"
#include "drawer.h"
#include <iostream>

int main(int argc, char **argv)
{
	/* initialize SDL */
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		assert(0 && "Failed to initialize video!");
		exit(-1);
	}

	if (TTF_Init() == -1)
	{
		assert(0 && "Failed to create ttf!");
		exit(-1);
	}
	
	SDL_Event event;
	SDL_Window* window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_OPENGL);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Drawer* drawer = Drawer::Create(window, renderer);
	Pacman* pacman = Pacman::Create(drawer);

	float last_frame = 0;
	float current_frame = 0;
	float elapsed_time = 0;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //no need to set every frame if not being changed

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
	{
		assert(0 && "Failed to initialize image types!");
		exit(-1);
	}

	if (!drawer)
	{
		assert(0 && "Failed to create drawer!");
		exit(-1);
	}
		
	if (!pacman)
	{
		assert(0 && "Failed to create game!");
		exit(-1);
	}
	
	if (!renderer)
	{
		assert(0 && "Failed to create renderer!");
		exit(-1);
	}

	if (!window)
	{
		assert(0 && "Failed to create window!");
		exit(-1);
	}

	while (SDL_PollEvent(&event) >= 0)
	{
		current_frame = SDL_GetTicks() * 0.001f;
		elapsed_time = current_frame - last_frame;
		last_frame = current_frame;

		if (!pacman->update(elapsed_time))
		{
			break;
		}

		pacman->draw();		

		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}

	if (drawer)
	{
		delete drawer;
		drawer = NULL;
	}

	if (pacman)
	{
		delete pacman;
		pacman = NULL;
	}

	if (renderer)
	{
		renderer = NULL;
	}

	if (window)
	{
		window = NULL;
	}

	TTF_Quit();
	IMG_Quit();
	SDL_Quit( );

	return 0;
}