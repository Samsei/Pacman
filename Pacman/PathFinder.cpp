#include "PathFinder.h"

#include <iostream>

//assign pointers
PathFinder::PathFinder(Avatar* avatar, World* main_world) :
	player(avatar),
	world(main_world)
{}

//destruct and set pointers to null
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

//work out the distance between two vectors
auto distance = [](Vector2f a, Vector2f b)
{
	return sqrtf(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
};

//get path based on current state
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

//the AStar algorithm, calculate the fastest path to a destination (not necessarily the shortest)
PathmapTile* PathFinder::AStar(std::list<PathmapTile*> tile_list, Vector2f destination, Vector2f ghost_current_tile, bool is_vulnerable)
{
	//find the starting tile and the end tile, set each tiles cost to infinity, parents to nullptr and if they have been visited to false
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

	//set the start tiles goal as the distance between the start tile and end tile
	start_tile->local_goal = 0.0f;
	start_tile->global_goal = distance(start_tile->returnTileAsVector(), destination);

	//set the current tile as the start tile and start the list of tiles not tested
	current_tile = start_tile;
	list_not_tested.push_back(start_tile);

	//while the list is not empty and the destination is not found -> this does not test all tiles, only until the goal is found
	while (!list_not_tested.empty() && current_tile != end_tile)
	{
		//sort the list by lowest to highest global cost
		list_not_tested.sort([](const PathmapTile* lhs, const PathmapTile* rhs) {return lhs->global_goal < rhs->global_goal; });

		//if the list is not empty and the first tile is visited, get rid of first tile
		while (!list_not_tested.empty() && list_not_tested.front()->is_visited)
		{
			list_not_tested.pop_front();
		}

		//if the list is empty, return
		if (list_not_tested.empty())
		{
			break;
		}

		//set the current tile to the first element of the list and set it as visited
		current_tile = list_not_tested.front();
		current_tile->is_visited = true;

		//get each neighbour for the current tile
		for (auto tile_neighbour : current_tile->tile_neighbours)
		{			
			//add the neighbour to the untested list
			list_not_tested.push_back(tile_neighbour);

			//set the lowest cost as the current tile
			lowest_cost = current_tile->local_goal + distance(current_tile->returnTileAsVector(), tile_neighbour->returnTileAsVector());

			//work out if the cost of the neighbouring tile is lower than the current cost
			//then set it as a child of the current tile, this finds the lowest cost path
			if (lowest_cost < tile_neighbour->local_goal)
			{
				tile_neighbour->parent = current_tile;
				tile_neighbour->local_goal = lowest_cost;
				tile_neighbour->global_goal = tile_neighbour->local_goal + distance(tile_neighbour->returnTileAsVector(), destination);
			}		
		}
	}
	//clear the list for the next time
	list_not_tested.clear();

	//find the highest cost tile (away from the player) while the ghost is vulnerable
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
		//work backwards from the goal to get the path, and set the next tile as the one before the start tile
		next_tile = end_tile;
		while (next_tile->parent != nullptr && next_tile->parent != start_tile)
		{
			next_tile = next_tile->parent;
		}
	}	

	//return the next tile in the path
	return next_tile;
}

//check if a tile is valid
bool PathFinder::tileIsValid(PathmapTile* tile)
{
	if (!tile->is_blocking && !tile->is_visited)
	{
		return true;
	}

	return false;
}