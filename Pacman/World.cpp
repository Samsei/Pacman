#include "World.h"


World::World(SDL_Renderer* renderer)
{
	bigDotSprite = new Sprite(renderer, "Big_Dot_32.png", 0, 0);;
	worldSprite = new Sprite(renderer, "playfield.png", 0, 0);;
}

World::~World(void)
{
	for (auto* dot : dots_list)
	{
		if (dot)
		{
			delete dot;
			dot = NULL;
		}		
	}

	for (auto* big_dot : big_dots_list)
	{
		if (big_dot)
		{
			delete big_dot;
			big_dot = NULL;
		}
	}

	for (auto* cherry : cherry_list)
	{
		if (cherry)
		{
			delete cherry;
			cherry = NULL;
		}
	}
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
				pathmap_tiles.push_back(tile);
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
					dots_list.push_back(dot);
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
					BigDot* big_dot = new BigDot(Vector2f(i*22, lineIndex*22), *sprite);
					big_dots_list.push_back(big_dot);
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
					cherry_list.push_back(cherry);
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

	for (auto* dot : dots_list)
	{
		renderer->draw(&dot->ReturnSprite(), dot->getPosition().x + 220, dot->getPosition().y + 60);
	}

	for (auto* big_dot : big_dots_list)
	{
		renderer->draw(&big_dot->ReturnSprite(), big_dot->getPosition().x + 220, big_dot->getPosition().y + 60);
	}

	for (auto* cherry : cherry_list)
	{
		renderer->draw(&cherry->ReturnSprite(), cherry->getPosition().x + 220, cherry->getPosition().y + 60);
	}
}

bool World::hasIntersectedDot(const Vector2f& position)
{
	auto it = std::find_if(dots_list.begin(), dots_list.end(), [&](Dot* dot) -> bool { return ((dot->getPosition() - position).Length() < 5.f); });

	if (dots_list.end() != it)
	{
		Dot* dot = *it;

		dots_list.remove(dot);
		delete dot;
		dot = NULL;

		return true;
	}	

	return false;
}

bool World::hasIntersectedBigDot(const Vector2f& position)
{
	auto it = std::find_if(big_dots_list.begin(), big_dots_list.end(), [&](BigDot* dot) -> bool { return ((dot->getPosition() - position).Length() < 5.f); });

	if (big_dots_list.end() != it)
	{
		BigDot* big_dot = *it;

		big_dots_list.remove(big_dot);
		delete big_dot;
		big_dot = NULL;

		return true;
	}

	return false;
}

bool World::hasIntersectedCherry(const Vector2f& position)
{
	auto it = std::find_if(cherry_list.begin(), cherry_list.end(), [&](Cherry* cherry) -> bool { return ((cherry->getPosition() - position).Length() < 5.f); });

	if (cherry_list.end() != it)
	{
		Cherry* cherry = *it;

		cherry_list.remove(cherry);
		delete cherry;
		cherry = NULL;

		return true;
	}

	return false;
}

bool World::tileIsValid(int x, int y)
{
	for (auto* tile : pathmap_tiles)
	{
		if (x == tile->x && y == tile->y && !tile->is_blocking)
		{
			return true;
		}
	}

	return false;
}