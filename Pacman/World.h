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

	void GetPath(int, int, int, int, std::list<PathmapTile*>&);
	bool getNextTile(PathmapTile*, std::list<PathmapTile*>&);

private:
	PathmapTile* GetTile(int, int);

	bool initPathMap();
	bool initDots(SDL_Renderer*);
	bool initBigDots(SDL_Renderer*);
	bool initCherrys(SDL_Renderer*);
	bool findPath(PathmapTile*, PathmapTile*, std::list<PathmapTile*>&);
	bool listDoesNotContain(PathmapTile*, std::list<PathmapTile*>&);	
	
	int la = 0;

	Vector2f player_pos = { 0, 0 };

	std::list<PathmapTile*> pathmap_tiles;
	std::list<Dot*> dots_list;
	std::list<BigDot*> big_dots_list;
	std::list<Cherry*> cherry_list;

	Sprite* dotSprite = nullptr;
	Sprite* bigDotSprite = nullptr;
	Sprite* worldSprite = nullptr;
};

#endif // WORLD_H