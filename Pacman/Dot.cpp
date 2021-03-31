#include "Dot.h"

Dot::Dot(SDL_Renderer* main_renderer, Vector2f position, const char* texture)
	: StaticGameEntity(main_renderer, position, texture)
{}

Dot::~Dot(void)
{}