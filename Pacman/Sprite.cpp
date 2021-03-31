#include "Sprite.h"

//create a sprite with the texture on the main renderer
Sprite::Sprite(SDL_Renderer* main_renderer, const char* entity_image, int x, int y) :
	image(entity_image),
	renderer(main_renderer)
{
	changeTexture(main_renderer, image, x, y);
}

//destruct pointers
Sprite::~Sprite()
{
	if (renderer)
	{
		renderer = NULL;
	}
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
	if (surface)
	{
		surface = NULL;
	}
}

//return the texture to render
SDL_Texture* Sprite::returnTexture()
{
	return texture;
}

//return size of texture
SDL_Rect* Sprite::returnSize()
{
	return &size_rect;
}

//return position of texture
SDL_Rect* Sprite::returnPos()
{
	return &position_rect;
}

//move the sprite
void Sprite::moveSprite(int x, int y)
{
	position_rect.x = x;
	position_rect.y = y;
	position_rect.w = size_rect.w;
	position_rect.h = size_rect.h;
}


//change the texture of the sprite (could possibly be done by storing multiple textures as an array)
void Sprite::changeTexture(SDL_Renderer* renderer, const char* image, int x, int y)
{
	surface = IMG_Load(image);

	size_rect.w = surface->w;
	size_rect.h = surface->h;

	position_rect.x = x;
	position_rect.y = y;
	position_rect.w = size_rect.w;
	position_rect.h = size_rect.h;

	//if the image doesn't load, exit
	if (!surface)
	{
		return;
	}

	//if there is a texture, destroy and assign a new one
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}