#pragma once

#include <vector>

#include "Avatar.h"
#include "World.h"

class PathFinder
{
public:
	PathFinder(std::list<PathmapTile*>, Avatar*, World*);
	~PathFinder();

	bool tileIsValid(PathmapTile*);

	PathmapTile* getPath(Avatar*, Vector2f, bool, bool);

private:
	PathmapTile* AStar(Vector2f, Vector2f, bool);

	float highest_cost = 0.0f;
	float lowest_cost = 0.0f;

	int neighbour_total = 0;

	bool path_found = false;

	const Vector2f ghost_spawn = { 13.0f, 13.0f };

	std::list<PathmapTile*> original_tile_list;
	std::list<PathmapTile*> list_not_tested;

	Avatar* player = nullptr;
	PathmapTile* current_tile = nullptr;
	PathmapTile* end_tile = nullptr;
	PathmapTile* next_tile = nullptr;
	PathmapTile* pt = nullptr;
	PathmapTile* prev = nullptr;
	PathmapTile* start_tile = nullptr;
	World* world = nullptr;
};