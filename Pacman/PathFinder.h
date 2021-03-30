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

	PathmapTile* AStar(std::list<PathmapTile*>, Vector2f, Vector2f, bool);
	PathmapTile* getPath(std::list<PathmapTile*>, Avatar*, Vector2f, bool, bool);
	PathmapTile* randomPath(std::list<PathmapTile*>);

private:
	bool isDestination(PathmapTile*, Avatar*);

	float highest_cost = 0;
	float lowest_cost = 0;
	float test = 0;

	int ghost_intelligence = 0;

	bool path_found = false;

	const Vector2f ghost_spawn = { 13.0f, 11.0f };

	std::list<PathmapTile*> list_not_tested;

	Avatar* player = nullptr;
	PathmapTile* current_tile = nullptr;
	PathmapTile* end_tile = nullptr;
	PathmapTile* next_tile = nullptr;
	PathmapTile* start_tile = nullptr;
	World* world = nullptr;

	PathmapTile* pt = nullptr;
	PathmapTile* prev = nullptr;
};