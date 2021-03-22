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

Drawer::Drawer(SDL_Window* window, SDL_Renderer* main_renderer)
: window(window)
, renderer(main_renderer)
{
	font = TTF_OpenFont("freefont-ttf\\sfd\\FreeMono.ttf", 24);
}

Drawer::~Drawer(void)
{
	TTF_CloseFont(font);
}

bool Drawer::init()
{
	if (!window)
	{
		return false;
	}

	return true;
}

void Drawer::draw(Sprite* sprite, int cell_x, int cell_y)
{
	SDL_RenderCopy(renderer, sprite->returnTexture(), sprite->returnSize(), sprite->returnPos());
}

void Drawer::drawText(const char* text, int x, int y)
{
	surface = TTF_RenderText_Solid(font, text, color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

    size_rect.x = 0;
    size_rect.y = 0;
    size_rect.w = surface->w;
    size_rect.h = surface->h;

    position_rect.x = x;
    position_rect.y = y;
	position_rect.w = size_rect.w;
	position_rect.h = size_rect.h;

	SDL_RenderCopy(renderer, texture, &size_rect, &position_rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);  //i think i did somehting here, need to check
}

SDL_Renderer* Drawer::returnRenderer()
{
	return renderer;
}