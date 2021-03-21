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
	
	SDL_Window* window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_OPENGL);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(!window)
	{
		assert(0 && "Failed to create window!");
		exit(-1);
	}

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	if (TTF_Init() == -1)
	{
		assert(0 && "Failed to create ttf!");
		exit(-1);
	}

	Drawer* drawer = Drawer::Create(window, renderer);
	Pacman* pacman = Pacman::Create(drawer);

	float lastFrame = (float) SDL_GetTicks() * 0.001f;
	SDL_Event event;

	float currentFrame = 0;
	float elapsedTime = 0;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //no need to set every frame if not being changed

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		exit(-1);//i'll add audio at some point
	}

	while (SDL_PollEvent(&event) >= 0)
	{
		SDL_RenderClear(renderer);

		currentFrame = (float) SDL_GetTicks() * 0.001f;
		elapsedTime = currentFrame - lastFrame;

		if (!pacman->Update(elapsedTime))
			break;
		
		pacman->Draw();
		
		lastFrame = currentFrame;		

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