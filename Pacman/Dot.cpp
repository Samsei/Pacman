#include "Dot.h"

//create a dot, passing the renderer, position, and image path
Dot::Dot(SDL_Renderer* main_renderer, Vector2f position, const char* texture)
	: StaticGameEntity(main_renderer, position, texture)
{}

Dot::~Dot(void)
{}