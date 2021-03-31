#include "BigDot.h"

//create a big dot, passing the renderer, position, and image path
BigDot::BigDot(SDL_Renderer* main_renderer, Vector2f position, const char* texture)
	: GameEntity(main_renderer, position, texture)
{}

BigDot::~BigDot(void)
{}