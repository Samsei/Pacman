#include "Drawer.h"

Drawer* Drawer::Create(SDL_Window* window, SDL_Renderer* main_renderer)
{
	Drawer* drawer = new Drawer(window, main_renderer);

	if (!drawer->init())
	{
		delete drawer;
		drawer = NULL;
	}

	return drawer;
}

Drawer::Drawer(SDL_Window* main_window, SDL_Renderer* main_renderer)
: window(main_window)
, renderer(main_renderer)
{
	font = TTF_OpenFont("freefont-ttf\\sfd\\FreeMono.ttf", 24);
}

Drawer::~Drawer(void)
{
	if (font)
	{
		TTF_CloseFont(font);
		font = NULL;
	}
	if (renderer)
	{
		SDL_RenderClear(renderer);
		renderer = NULL;
	}
	if (surface)
	{
		surface = NULL;
	}
	if (texture)
	{
		texture = NULL;
	}
	if (window)
	{
		window = NULL;
	}
}

bool Drawer::init()
{
	if (!window)
	{
		return false;
	}

	return true;
}

void Drawer::draw(Sprite* sprite)
{
	SDL_RenderCopy(renderer, sprite->returnTexture(), sprite->returnSize(), sprite->returnPos());
}

void Drawer::drawText(const char* text, int x, int y)
{
	surface = TTF_RenderText_Solid(font, text, color);

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

	SDL_RenderCopy(renderer, texture, &size_rect, &position_rect);
	SDL_FreeSurface(surface);
}

SDL_Renderer* Drawer::returnRenderer()
{
	return renderer;
}