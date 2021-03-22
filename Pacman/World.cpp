#include "World.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "PathmapTile.h"
#include "Dot.h"
#include "BigDot.h"
#include "Drawer.h"
#include "Cherry.h"

World::World(SDL_Renderer* renderer)
{
	bigDotSprite = new Sprite(renderer, "Big_Dot_32.png", 0, 0);;
	worldSprite = new Sprite(renderer, "playfield.png", 0, 0);;
}

World::~World(void)
{
}

void World::init(Drawer* renderer)
{
	initPathMap();
	initDots(renderer->returnRenderer());
	initBigDots(renderer->returnRenderer());
	initCherrys(renderer->returnRenderer());
}

bool World::initPathMap()
{
	std::string line;
	std::ifstream myfile ("map.txt");
	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			std::getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				PathmapTile* tile = new PathmapTile(i, lineIndex, (line[i] == 'x'));
				myPathmapTiles.push_back(tile);
			}

			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

bool World::initDots(SDL_Renderer* renderer)
{
	std::string line;
	std::ifstream myfile ("map.txt");

	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			std::getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				if (line[i] == '.')
				{
					Sprite* sprite = new Sprite(renderer, "Small_Dot_32.png", i * 22 + 220, lineIndex * 22 + 60);
					Dot* dot = new Dot(Vector2f(i*22, lineIndex*22), *sprite);
					myDots.push_back(dot);
				}
			}

			lineIndex++;
		}
		myfile.close();
	}
	return true;
}

bool World::initBigDots(SDL_Renderer* renderer)
{
	std::string line;
	std::ifstream myfile ("map.txt");

	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			std::getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				if (line[i] == 'o')
				{
					Sprite* sprite = new Sprite(renderer, "Big_Dot_32.png", i * 22 + 220, lineIndex * 22 + 60);
					BigDot* dot = new BigDot(Vector2f(i*22, lineIndex*22), *sprite);
					myBigDots.push_back(dot);
				}
			}

			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

bool World::initCherrys(SDL_Renderer* renderer)
{
	std::string line;
	std::ifstream myfile("map.txt");

	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (!myfile.eof())
		{
			std::getline(myfile, line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				if (line[i] == 'c')
				{
					Sprite* sprite = new Sprite(renderer, "cherry.png", i * 22 + 220, lineIndex * 22 + 60);
					Cherry* cherry = new Cherry(Vector2f(i * 22, lineIndex * 22), *sprite);
					myCherry.push_back(cherry);
				}
			}

			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

void World::draw(Drawer* renderer)
{
	renderer->draw(worldSprite);

	for (auto* dot : myDots)
	{
		renderer->draw(&dot->ReturnSprite(), dot->getPosition().x + 220, dot->getPosition().y + 60);
	}

	for (auto* dot : myBigDots)
	{
		renderer->draw(&dot->ReturnSprite(), dot->getPosition().x + 220, dot->getPosition().y + 60);
	}

	for (auto* cherry : myCherry)
	{
		renderer->draw(&cherry->ReturnSprite(), cherry->getPosition().x + 220, cherry->getPosition().y + 60);
	}
}

bool World::tileIsValid(int x, int y)
{
	for(std::list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;

		if (x == tile->x && y == tile->y && !tile->is_blocking)
		{
			return true;
		}
	}

	return false;
}

bool World::hasIntersectedDot(const Vector2f& position)
{
	auto it = std::find_if(myDots.begin(), myDots.end(), [&](Dot* dot) -> bool { return ((dot->getPosition() - position).Length() < 5.f); });

	if (myDots.end() != it)
	{
		Dot* dot = *it;
		myDots.remove(dot);
		delete dot;
		return true;
	}	

	return false;
}

bool World::hasIntersectedBigDot(const Vector2f& position)
{
	auto it = std::find_if(myBigDots.begin(), myBigDots.end(), [&](BigDot* dot) -> bool { return ((dot->getPosition() - position).Length() < 5.f); });

	if (myBigDots.end() != it)
	{
		BigDot* dot = *it;
		myBigDots.remove(dot);
		delete dot;
		return true;
	}

	return false;
}

bool World::hasIntersectedCherry(const Vector2f& position)
{
	return true;
}

void World::GetPath(int from_x, int from_y, int to_x, int to_y, std::list<PathmapTile*>& list)
{
	PathmapTile* fromTile = GetTile(from_x, from_y);
	PathmapTile* toTile = GetTile(to_x, to_y);

	for(std::list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;
		tile->is_visited = false;
	}

	findPath(fromTile, toTile, list);
}

PathmapTile* World::GetTile(int from_x, int from_y)
{
	for(std::list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;
		if (tile->x == from_x && tile->y == from_y)
		{
			return tile;
		}
	}

	return NULL;
}

bool World::listDoesNotContain(PathmapTile* from_tile, std::list<PathmapTile*>& list)
{
	for(std::list<PathmapTile*>::iterator list_iter = list.begin(); list_iter != list.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;
		if (tile == from_tile)
		{
			return false;
		}
	}

	return true;
}

bool SortFromGhostSpawn(PathmapTile* a, PathmapTile* b)
{
	int la = abs(a->x - 13) + abs(a->y - 13);
	int lb = abs(b->x - 13) + abs(b->y - 13);

    return la < lb;
}

bool World::findPath(PathmapTile* from_tile, PathmapTile* to_tile, std::list<PathmapTile*>& list)
{
	from_tile->is_visited = true;

	if (from_tile->is_blocking)
	{
		return false;
	}
	
	if (from_tile == to_tile)
	{
		return true;
	}

	std::list<PathmapTile*> neighborList;

	up = GetTile(from_tile->x, from_tile->y - 1);
	down = GetTile(from_tile->x, from_tile->y + 1);
	right = GetTile(from_tile->x + 1, from_tile->y);
	left = GetTile(from_tile->x - 1, from_tile->y);

	if (up && !up->is_visited && !up->is_blocking && listDoesNotContain(up, list))
	{
		neighborList.push_front(up);
	}
	if (down && !down->is_visited && !down->is_blocking && listDoesNotContain(down, list))
	{
		neighborList.push_front(down);
	}
	if (right && !right->is_visited && !right->is_blocking && listDoesNotContain(right, list))
	{
		neighborList.push_front(right);
	}
	if (left && !left->is_visited && !left->is_blocking && listDoesNotContain(left, list))
	{
		neighborList.push_front(left);
	}

	neighborList.sort(SortFromGhostSpawn);

	for(std::list<PathmapTile*>::iterator list_iter = neighborList.begin(); list_iter != neighborList.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;

		list.push_back(tile);

		if (findPath(tile, to_tile, list))
		{
			return true;
		}

		list.pop_back();
	}

	return false;
}