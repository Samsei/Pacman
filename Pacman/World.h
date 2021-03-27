#ifndef WORLD_H
#define WORLD_H

#include <list>
#include <fstream>
#include <string>

#include "PathmapTile.h"
#include "Dot.h"
#include "BigDot.h"
#include "Cherry.h"
#include "Drawer.h"

class Drawer;
class PathmapTile;
class Dot;
class BigDot;
class Cherry;

class World
{
public:
	World(SDL_Renderer*);
	~World(void);

	void init(Drawer*);
	void draw(Drawer*);

	bool tileIsValid(int, int);
	bool hasIntersectedDot(const Vector2f&);
	bool hasIntersectedBigDot(const Vector2f&);
	bool hasIntersectedCherry(const Vector2f&);

private:
	int line_index = 0;
	int la = 0;

	Vector2f player_pos = { 0, 0 };

	std::list<PathmapTile*> pathmap_tiles;
	std::list<Dot*> dots_list;
	std::list<BigDot*> big_dots_list;
	std::list<Cherry*> cherry_list;

	std::string line = "";
	std::ifstream my_file;

	PathmapTile* tile = nullptr;

	SDL_Renderer* main_renderer = nullptr;

	Sprite* dotSprite = nullptr;
	Sprite* bigDotSprite = nullptr;
	Sprite* worldSprite = nullptr;
};

#endif // WORLD_H