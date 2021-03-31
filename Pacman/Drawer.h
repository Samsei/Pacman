#ifndef DRAWER_H
#define DRAWER_H

#include "SDL_ttf.h"
#include "Sprite.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

class Drawer
{
public:
	static Drawer* Create(SDL_Window*, SDL_Renderer*);
	~Drawer(void);

	void draw(Sprite*);
	void drawText(const char*, int, int);

	SDL_Renderer* returnRenderer();

private:
	Drawer(SDL_Window*, SDL_Renderer*);
	
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Window* window = nullptr;

	SDL_Color color = { 255, 0, 0, 255 };
	SDL_Rect position_rect = { 0, 0 , 0 , 0};
	SDL_Rect size_rect = { 0, 0 , 0 , 0 };

	TTF_Font* font = nullptr;
};

#endif // DRAWER_H