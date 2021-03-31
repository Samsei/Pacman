#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* main_renderer, const char* image, int x, int y) :
	image(image),
	renderer(main_renderer)
{
	changeTexture(main_renderer, image, x, y);
}

SDL_Texture* Sprite::returnTexture()
{
	return texture;
}

SDL_Rect* Sprite::returnSize()
{
	return &size_rect;
}

SDL_Rect* Sprite::returnPos()
{
	return &position_rect;
}

void Sprite::moveSprite(int x, int y)
{
	position_rect.x = x;
	position_rect.y = y;
	position_rect.w = size_rect.w;
	position_rect.h = size_rect.h;
}

void Sprite::changeTexture(SDL_Renderer* renderer, const char* image, int x, int y)
{
	surface = IMG_Load(image);

	if (!surface)
		return;

	if (texture)
	{
		SDL_DestroyTexture(texture);
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	size_rect.w = surface->w;
	size_rect.h = surface->h;

	position_rect.x = x;
	position_rect.y = y;
	position_rect.w = size_rect.w;
	position_rect.h = size_rect.h;

	SDL_FreeSurface(surface);
}