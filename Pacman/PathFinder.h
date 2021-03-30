#pragma once

#include <vector>
#include <Bits.h>

#include "Avatar.h"
#include "World.h"

class PathFinder
{
public:
	PathFinder(Avatar*, int, World*);

	bool tileIsValid(PathmapTile*);

	PathmapTile* getPath(std::list<PathmapTile*>, Avatar*, Vector2f);

private:
	bool isDestination(PathmapTile*, Avatar*);

	int ghost_intelligence = 0;

	float lowest_cost = 0;
	float test = 0;

	bool path_found = false;

	Avatar* player = nullptr;
	World* world = nullptr;

	PathmapTile* current_tile = nullptr;
	PathmapTile* start_tile = nullptr;
	PathmapTile* end_tile = nullptr;
	PathmapTile* next_tile = nullptr;

	std::list<PathmapTile*> list_not_tested;
};