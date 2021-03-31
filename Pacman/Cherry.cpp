#include "Cherry.h"

Cherry::Cherry(SDL_Renderer* main_renderer, Vector2f position, const char* texture)
	: StaticGameEntity(main_renderer, position, texture)
{}

Cherry::~Cherry(void)
{}