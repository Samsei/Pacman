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

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		exit(-1);//i'll add audio at some point
	}

	SDL_Window* window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_OPENGL);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Drawer* drawer = Drawer::Create(window, renderer);
	Pacman* pacman = Pacman::Create(drawer);
	
	if (!window)
	{
		assert(0 && "Failed to create window!");
		exit(-1);
	}

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //no need to set every frame if not being changed

	SDL_Event event;

	float last_frame = (float)SDL_GetTicks() * 0.001f;
	float current_frame = 0;
	float elapsed_time = 0;
	

	while (SDL_PollEvent(&event) >= 0)
	{
		SDL_RenderClear(renderer);

		current_frame = (float) SDL_GetTicks() * 0.001f;
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

	delete pacman;
	delete drawer;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit( );

	return 0;
}