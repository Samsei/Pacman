#include "PathFinder.h"

#include <iostream>

PathFinder::PathFinder(Avatar* avatar, int intelligence, World* main_world) :
	player(avatar),
	ghost_intelligence(intelligence),
	world(main_world)
{

}

auto distance = [](Vector2f a, Vector2f b)
{
	return sqrtf(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
};

PathmapTile* PathFinder::getPath(std::list<PathmapTile*> tile_list, Avatar* player, Vector2f ghost_current_tile, bool is_vulnerable, bool is_dead)
{
	if (!is_vulnerable && !is_dead)
	{
		if (ghost_intelligence == 1)
		{
			return AStar(tile_list, Vector2f{ player->getCurrentTile().x, player->getCurrentTile().y }, ghost_current_tile, is_vulnerable);
		}

		if (ghost_intelligence == 2)
		{
			return randomPath(tile_list);
		}
	}

	else if (is_vulnerable)
	{
		return AStar(tile_list, Vector2f{ player->getCurrentTile().x, player->getCurrentTile().y }, ghost_current_tile, is_vulnerable);
	}
	
	else if (is_dead)
	{
		return AStar(tile_list, ghost_spawn, ghost_current_tile, is_vulnerable);
	}
}

PathmapTile* PathFinder::randomPath(std::list<PathmapTile*>)
{
	return nullptr;
}

PathmapTile* PathFinder::AStar(std::list<PathmapTile*> tile_list, Vector2f destination, Vector2f ghost_current_tile, bool is_vulnerable)
{
	for (PathmapTile* p : tile_list)
	{
		if (p->x == ghost_current_tile.x && p->y == ghost_current_tile.y)
		{
			start_tile = p;
		}

		if (p->x == destination.x && p->y == destination.y)
		{
			end_tile = p;
		}

		p->global_goal = INFINITY;
		p->local_goal = INFINITY;
		p->parent = nullptr;
		p->is_visited = false;
	}

	start_tile->local_goal = 0.0f;
	start_tile->global_goal = distance(Vector2f{ start_tile->x, start_tile->y }, Vector2f{ destination.x, destination.y });

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

			test = current_tile->local_goal + distance(Vector2f{ current_tile->x, current_tile->y }, Vector2f{ tile_neighbour->x, tile_neighbour->y });

			if (test < tile_neighbour->local_goal)
			{
				tile_neighbour->parent = current_tile;
				tile_neighbour->local_goal = test;
				tile_neighbour->global_goal = tile_neighbour->local_goal + distance(Vector2f{ tile_neighbour->x, tile_neighbour->y }, Vector2f{ destination.x, destination.y });
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
	
	if (!tile->is_blocking && !tile->is_spawn && !tile->is_visited)
	{
		return true;
	}

	return false;
}

bool PathFinder::isDestination(PathmapTile* tile, Avatar* player)
{
	return (tile->x == player->getCurrentTile().x && tile->y == player->getCurrentTile().y);
}