#include "BigDot.h"

BigDot::BigDot(SDL_Renderer* main_renderer, Vector2f position, const char* texture)
	: StaticGameEntity(main_renderer, position, texture)
{}

BigDot::~BigDot(void)
{}