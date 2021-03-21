#ifndef DRAWER_H
#define DRAWER_H

#include "Sprite.h"
#include "SDL_ttf.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

class Drawer
{
public:
	static Drawer* Create(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	~Drawer(void);

	void Draw(Sprite* sprite, int aCellX = 0, int aCellY = 0);
	void DrawText(const char* aText, int aX, int aY);
	SDL_Renderer* ReturnRenderer();

private:
	Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	bool Init();
	
	SDL_Window* myWindow;
	SDL_Renderer* myRenderer;
	SDL_Surface* surface;
	SDL_Texture* optimizedSurface;

	TTF_Font* font;
	SDL_Color fg = { 255,0,0,255 };

	SDL_Rect posRect;
	SDL_Rect sizeRect;
};

#endif // DRAWER_H