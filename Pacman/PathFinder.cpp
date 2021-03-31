#include "PathFinder.h"

#include <iostream>

PathFinder::PathFinder(Avatar* avatar, World* main_world) :
	player(avatar),
	world(main_world)
{
	srand(time(NULL));
}

PathFinder::~PathFinder()
{
	if (player)
	{
		player = NULL;
	}
	if (current_tile)
	{
		current_tile = NULL;
	}
	if (end_tile)
	{
		end_tile = NULL;
	}
	if (next_tile)
	{
		next_tile = NULL;
	}
	if (start_tile)
	{
		start_tile = NULL;
	}
	if (world)
	{
		world = NULL;
	}
	if (pt)
	{
		pt = NULL;
	}
	if (prev)
	{
		prev = NULL;
	}
}

auto distance = [](Vector2f a, Vector2f b)
{
	return sqrtf(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
};

PathmapTile* PathFinder::getPath(std::list<PathmapTile*> tile_list, Avatar* player, Vector2f ghost_current_tile, bool is_vulnerable, bool is_dead)
{
	if (!is_vulnerable && !is_dead)
	{		
		return AStar(tile_list, player->getCurrentTile(), ghost_current_tile, is_vulnerable);
	}

	else if (is_vulnerable)
	{
		return AStar(tile_list, player->getCurrentTile(), ghost_current_tile, is_vulnerable);
	}
	
	else if (is_dead)
	{
		return AStar(tile_list, ghost_spawn, ghost_current_tile, is_vulnerable);
	}

	return nullptr;
}

PathmapTile* PathFinder::AStar(std::list<PathmapTile*> tile_list, Vector2f destination, Vector2f ghost_current_tile, bool is_vulnerable)
{
	for (PathmapTile* p : tile_list)
	{
		if (p->returnTileAsVector() == ghost_current_tile)
		{
			start_tile = p;
		}

		if (p->returnTileAsVector() == destination)
		{
			end_tile = p;
		}

		p->global_goal = INFINITY;
		p->local_goal = INFINITY;
		p->parent = nullptr;
		p->is_visited = false;
	}

	start_tile->local_goal = 0.0f;
	start_tile->global_goal = distance(start_tile->returnTileAsVector(), destination);

	current_tile = start_tile;
	list_not_tested.push_back(start_tile);


	while (!list_not_tested.empty() && current_tile != end_tile)
	{
		list_not_tested.sort([](const PathmapTile* lhs, const PathmapTile* rhs) {return lhs->global_goal < rhs->global_goal; });

		while (!list_not_tested.empty() && list_not_tested.front()->is_visited)
		{
			list_not_tested.pop_front();
		}

		if (list_not_tested.empty())
		{
			break;
		}

		current_tile = list_not_tested.front();
		current_tile->is_visited = true;

		for (auto tile_neighbour : current_tile->tile_neighbours)
		{			
			list_not_tested.push_back(tile_neighbour);

			lowest_cost = current_tile->local_goal + distance(current_tile->returnTileAsVector(), tile_neighbour->returnTileAsVector());

			if (lowest_cost < tile_neighbour->local_goal)
			{
				tile_neighbour->parent = current_tile;
				tile_neighbour->local_goal = lowest_cost;
				tile_neighbour->global_goal = tile_neighbour->local_goal + distance(tile_neighbour->returnTileAsVector(), destination);
			}		
		}
	}
	list_not_tested.clear();

	if (is_vulnerable)
	{		
		for (auto tile_neighbour : start_tile->tile_neighbours)
		{
			if (tile_neighbour->global_goal > highest_cost && !tile_neighbour->is_blocking && tile_neighbour != pt)
			{
				highest_cost = tile_neighbour->global_goal;
			}
		}
		for (auto tile_neighbour : start_tile->tile_neighbours)
		{
			if (tile_neighbour->global_goal >= highest_cost && tile_neighbour != prev && !tile_neighbour->is_blocking)
			{
				pt = tile_neighbour;
			}
		}
		highest_cost = 0;
		return pt;
	}

	else
	{
		next_tile = end_tile;
		while (next_tile->parent != nullptr && next_tile->parent != start_tile)
		{
			next_tile = next_tile->parent;
		}
	}	

	return next_tile;
}

bool PathFinder::tileIsValid(PathmapTile* tile)
{
	if (!tile->is_blocking && !tile->is_visited)
	{
		return true;
	}

	return false;
}