#include "Drawer.h"
#include "SDL.h"
#include "SDL_image.h"

Drawer* Drawer::Create(SDL_Window* aWindow, SDL_Renderer* aRenderer)
{
	Drawer* drawer = new Drawer(aWindow, aRenderer);

	if (!drawer->Init())
	{
		delete drawer;
		drawer = NULL;
	}

	return drawer;
}

Drawer::Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer)
: myWindow(aWindow)
, myRenderer(aRenderer)
{
	font = TTF_OpenFont("freefont-ttf\\sfd\\FreeMono.ttf", 24);
}

Drawer::~Drawer(void)
{
	TTF_CloseFont(font);
}

bool Drawer::Init()
{
	if (!myWindow)
		return false;

	return true;
}

void Drawer::Draw(Sprite* sprite, int aCellX, int aCellY)
{
	SDL_RenderCopy(myRenderer, sprite->returnTexture(), sprite->returnSize(), sprite->returnPos());
}

void Drawer::DrawText(const char* aText, int aX, int aY)
{
	surface = TTF_RenderText_Solid(font, aText, fg);
	optimizedSurface = SDL_CreateTextureFromSurface(myRenderer, surface);

    sizeRect.x = 0;
    sizeRect.y = 0;
    sizeRect.w = surface->w;
    sizeRect.h = surface->h;

    posRect.x = aX;
    posRect.y = aY;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(myRenderer, optimizedSurface, &sizeRect, &posRect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(optimizedSurface);  //i think i did somehting here, need to check
}

SDL_Renderer* Drawer::ReturnRenderer()
{
	return myRenderer;
}