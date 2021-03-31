#include "Drawer.h"

//create a drawer with pointers to the window and the renderer
Drawer* Drawer::Create(SDL_Window* window, SDL_Renderer* main_renderer)
{
	Drawer* drawer = new Drawer(window, main_renderer);

	//if there is no window, delete the drawer 
	if (!window)
	{
		delete drawer;
		drawer = NULL;
	}

	return drawer;
}

//open the font and store at creation, and assign the window and renderer to pointers
Drawer::Drawer(SDL_Window* main_window, SDL_Renderer* main_renderer)
: window(main_window)
, renderer(main_renderer)
{
	font = TTF_OpenFont("freefont-ttf\\sfd\\FreeMono.ttf", 24);
}

//destruct pointers
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

//draw the sprites that are passed through
void Drawer::draw(Sprite* sprite)
{
	SDL_RenderCopy(renderer, sprite->returnTexture(), sprite->returnSize(), sprite->returnPos());
}

//create and draw the text at the specified x and y
void Drawer::drawText(const char* text, int x, int y)
{
	surface = TTF_RenderText_Solid(font, text, color);

	size_rect.w = surface->w;
	size_rect.h = surface->h;

	position_rect.x = x;
	position_rect.y = y;
	position_rect.w = size_rect.w;
	position_rect.h = size_rect.h;

	//destroy the previous texture
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);	
	SDL_FreeSurface(surface);

	SDL_RenderCopy(renderer, texture, &size_rect, &position_rect);
}

//return the pointer to the main renderer
SDL_Renderer* Drawer::returnRenderer()
{
	return renderer;
}