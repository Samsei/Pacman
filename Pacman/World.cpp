#include "World.h"


World::World(SDL_Renderer* renderer) :
	main_renderer(renderer)
{
	world_sprite = new Sprite(renderer, "playfield.png", 0, 0);;
}

World::~World(void)
{
	for (Dot* dot : dots_list)
	{
		if (dot)
		{
			delete dot;
			dot = NULL;
		}		
	}

	for (BigDot* big_dot : big_dots_list)
	{
		if (big_dot)
		{
			delete big_dot;
			big_dot = NULL;
		}
	}

	for (Cherry* cherry : cherry_list)
	{
		if (cherry)
		{
			delete cherry;
			cherry = NULL;
		}
	}

	for (PathmapTile* path : pathmap_tiles)
	{
		if (path)
		{
			delete path;
			path = NULL;
		}		
	}
}

void World::init()
{
	my_file.open("map.txt");

	if (my_file.is_open())
	{
		line_index = 0;
		while (!my_file.eof())
		{
			std::getline(my_file, line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				tile = new PathmapTile(i, line_index, (line[i] == 'x'));
				pathmap_tiles.push_back(tile);

				if (line[i] == 't')
				{
					tile->is_teleport = true;

					if (teleport_1 == nullptr)
					{
						teleport_1 = tile;
					}
					else if (teleport_2 == nullptr)
					{
						teleport_2 = tile;
					}
				}

				if (line[i] == '.')
				{
					Dot* dot = new Dot(main_renderer, Vector2f(i * tile_size, line_index * tile_size));
					dots_list.push_back(dot);
				}

				else if (line[i] == 'o')
				{
					BigDot* big_dot = new BigDot(main_renderer, Vector2f(i * tile_size, line_index * tile_size));
					big_dots_list.push_back(big_dot);
				}

				else if (line[i] == 'c')
				{
					Cherry* cherry = new Cherry(main_renderer, Vector2f(i * tile_size, line_index * tile_size));
					cherry_list.push_back(cherry);
				}
			}

			line_index++;
		}
		my_file.close();
	}

	for (PathmapTile* tile_n : pathmap_tiles)
	{
		if (!tile_n->is_blocking)
		{
			for (PathmapTile* neighbouring_tile : pathmap_tiles)
			{
				if (!neighbouring_tile->is_blocking ||
					tile_n != neighbouring_tile || 
				   ((tile_n->x - neighbouring_tile->x < 1 ||
					tile_n->x - neighbouring_tile->x > -1) &&
					(tile_n->y - neighbouring_tile->y < 1 || 
					tile_n->y - neighbouring_tile->y > -1)))
				{
					for (int x = -1; x <= 1; x++)
					{
						if (x == 0)
						{
							for (int y = -1; y <= 1; y++)
							{
								if (y != 0 && tile_n->x == neighbouring_tile->x && tile_n->y + y == neighbouring_tile->y)
								{
									tile_n->tile_neighbours.push_back(neighbouring_tile);
								}
							}
						}
						else if (tile_n->x + x == neighbouring_tile->x && tile_n->y == neighbouring_tile->y)
						{
							tile_n->tile_neighbours.push_back(neighbouring_tile);
						}
					}
				}			
			}
		}
	}
}

void World::draw(Drawer* renderer)
{
	renderer->draw(world_sprite);

	for (Dot* dot : dots_list)
	{
		dot->draw(renderer);
	}

	for (BigDot* big_dot : big_dots_list)
	{
		big_dot->draw(renderer);
	}

	for (Cherry* cherry : cherry_list)
	{
		cherry->draw(renderer);
	}
}

bool World::hasIntersectedDot(const Vector2f& position)
{
	for (Dot* dot : dots_list)
	{
		if (dot->intersect(position))
		{
			dots_list.remove(dot);
			delete dot;
			dot = NULL;

			return true;
		}
	}

	return false;
}

bool World::hasIntersectedBigDot(const Vector2f& position)
{
	for (BigDot* big_dot : big_dots_list)
	{
		if (big_dot->intersect(position))
		{
			big_dots_list.remove(big_dot);
			delete big_dot;
			big_dot = NULL;

			return true;
		}
	}

	return false;
}

bool World::hasIntersectedCherry(const Vector2f& position)
{
	for (Cherry* cherry : cherry_list)
	{
		if (cherry->intersect(position))
		{
			cherry_list.remove(cherry);
			delete cherry;
			cherry = NULL;

			return true;
		}
	}

	return false;
}

bool World::checkDotList()
{
	if (dots_list.empty())
	{
		return true;
	}
	return false;
}

bool World::tileIsValid(int x, int y)
{
	for (PathmapTile* tile : pathmap_tiles)
	{
		if (x == tile->x && y == tile->y && !tile->is_blocking)
		{
			return true;
		}
	}

	return false;
}

Vector2f World::tileIsTeleport(int x, int y)
{
	if (x == teleport_1->x && y == teleport_1->y)
	{
		return Vector2f{ teleport_2->x, teleport_2->y };
	}
	else if (x == teleport_2->x && y == teleport_2->y)
	{
		return Vector2f{ teleport_1->x, teleport_1->y };
	}
	return Vector2f{ 0, 0 };
}

std::list<PathmapTile*> World::returnTiles()
{
	return pathmap_tiles;
}