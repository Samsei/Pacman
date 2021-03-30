#pragma once
#include "SDL.h"
#include "SDL_image.h"

class Sprite
{
public:
	Sprite() = default;
	Sprite(SDL_Renderer*, const char*, int = 0, int = 0);
	~Sprite() = default;

	SDL_Texture* returnTexture();
	SDL_Rect* returnSize();
	SDL_Rect* returnPos();

	void changeTexture(SDL_Renderer*, const char*, int = 0, int = 0);
	void moveSprite(int = 0, int = 0);

private:
	const char* image = nullptr;

	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = nullptr;

	SDL_Rect size_rect = { 0, 0 , 0 , 0 };
	SDL_Rect position_rect = { 0, 0 , 0 , 0 };
};

