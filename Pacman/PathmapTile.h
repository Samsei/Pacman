#ifndef PATHMAPTILE_H
#define PATHMAPTILE_H

#include <vector>

#include "Vector2f.h"

class PathmapTile
{
public:
	PathmapTile(int, int, bool);
	~PathmapTile();

	Vector2f returnTileAsVector();

	bool is_blocking = false;
	bool is_teleport = false;
	bool is_visited = false;

	float global_goal = INFINITY;
	float local_goal = INFINITY;
	float x = 0.0f;
	float y = 0.0f;

	std::vector<PathmapTile*> tile_neighbours;

	PathmapTile* parent = nullptr;
};

#endif // PATHMAPTILE_H