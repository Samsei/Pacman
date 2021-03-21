#pragma once
#include "SDL.h"
#include "SDL_image.h"

class Sprite
{
public:
	Sprite() = default;
	Sprite(SDL_Renderer* aRenderer, const char* anImage, int aCellX = 0, int aCellY = 0);
	~Sprite() = default;
	SDL_Texture* returnTexture();
	SDL_Rect* returnSize();
	SDL_Rect* returnPos();
	void MoveSprite(int aCellX = 0, int aCellY = 0);
	void ChangeTexture(SDL_Renderer* aRenderer, const char* anImage, int aCellX = 0, int aCellY = 0);
private:
	SDL_Renderer* myRenderer;
	SDL_Texture* texture;
	SDL_Surface* surface;
	SDL_Rect sizeRect;
	SDL_Rect posRect;

	const char* image;
};

