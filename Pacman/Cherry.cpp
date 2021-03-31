#include "Cherry.h"

//create a cherry, passing the renderer, position, and image path
Cherry::Cherry(SDL_Renderer* main_renderer, Vector2f position, const char* texture)
	: StaticGameEntity(main_renderer, position, texture)
{}

Cherry::~Cherry(void)
{}