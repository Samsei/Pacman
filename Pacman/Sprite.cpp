#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* aRenderer, const char* anImage, int aCellX, int aCellY) :
	image(anImage),
	myRenderer(aRenderer)
{
	ChangeTexture(aRenderer, anImage, aCellX, aCellY);
}

SDL_Texture* Sprite::returnTexture()
{
	return texture;
}

SDL_Rect* Sprite::returnSize()
{
	return &sizeRect;
}

SDL_Rect* Sprite::returnPos()
{
	return &posRect;
}

void Sprite::MoveSprite(int aCellX, int aCellY)
{
	posRect.x = aCellX;
	posRect.y = aCellY;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;
}

void Sprite::ChangeTexture(SDL_Renderer* aRenderer, const char* anImage, int aCellX, int aCellY)
{
	surface = IMG_Load(anImage);

	if (!surface)
		return;

	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(aRenderer, surface);

	sizeRect.x = 0;
	sizeRect.y = 0;
	sizeRect.w = surface->w;
	sizeRect.h = surface->h;

	posRect.x = aCellX;
	posRect.y = aCellY;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_FreeSurface(surface);
}