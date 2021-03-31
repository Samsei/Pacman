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

	void init();
	void draw(Drawer*);

	bool checkDotList();
	bool hasIntersectedBigDot(const Vector2f&);
	bool hasIntersectedCherry(const Vector2f&);
	bool hasIntersectedDot(const Vector2f&);
	bool tileIsValid(Vector2f);

	Vector2f tileIsTeleport(Vector2f);

	std::list<PathmapTile*> returnTiles();

private:
	int line_index = 0;

	const int height_offset = 60;
	const int width_offset = 220;
	const int tile_size = 22;

	Vector2f player_pos = { 0, 0 };

	std::list<BigDot*> big_dots_list;
	std::list<Cherry*> cherry_list;
	std::list<Dot*> dots_list;
	std::list<PathmapTile*> pathmap_tiles;

	std::ifstream my_file;
	std::string line = "";

	PathmapTile* tile = nullptr;
	PathmapTile* teleport_1 = nullptr;
	PathmapTile* teleport_2 = nullptr;
	SDL_Renderer* main_renderer = nullptr;
	Sprite* dot_sprite = nullptr;
	Sprite* big_dot_sprite = nullptr;
	Sprite* world_sprite = nullptr;
};

#endif // WORLD_H