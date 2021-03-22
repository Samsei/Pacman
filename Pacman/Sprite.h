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

	void moveSprite(int = 0, int = 0);
	void changeTexture(SDL_Renderer*, const char*, int = 0, int = 0);
private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Surface* surface;

	SDL_Rect size_rect;
	SDL_Rect position_rect;

	const char* image;
};

