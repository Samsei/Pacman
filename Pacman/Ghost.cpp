#include "Ghost.h"

Ghost::Ghost(SDL_Renderer* main_renderer, const Vector2f& entity_position, const char* sprite_texture, Avatar* player, World* main_world, const Vector2f ghost_spawn) :
	MovableGameEntity(main_renderer, entity_position, sprite_texture, ghost_spawn),
	world(main_world),
	renderer(main_renderer),
	spawn(ghost_spawn),
	pacman(player)
{
	path_finder = new PathFinder(player, world);

	entity_next_tile = current_tile;
}

Ghost::~Ghost()
{
	if (next_tile)
	{
		next_tile = NULL;
	}
	if (path_finder)
	{
		delete path_finder;
		path_finder = NULL;
	}	
	if (world)
	{
		world = NULL;
	}
	if (renderer)
	{
		renderer = NULL;
	}
}

void Ghost::setDead()
{
	is_vulnerable = false;
	is_dead = true;
	speed = 120.f;
	changeState();
}

void Ghost::setNormal()
{
	is_vulnerable = false;
	is_dead = false;
	speed = 30;
	changeState();
}

void Ghost::setVulnerable()
{
	is_vulnerable = true;
	speed = 20;
	changeState();
}

void Ghost::update(float delta_time)
{
	getNextTile();
	changeDirection();
	moveEntity(delta_time);
	moveSprite();
}

void Ghost::getNextTile()
{
	if (isAtDestination())
	{
		next_tile = path_finder->getPath(world->returnTiles(), pacman, current_tile, is_vulnerable, is_dead);
		entity_next_tile = 
		{ 
			next_tile->x, 
			next_tile->y
		};
	}

	if (is_dead && current_tile == spawn)
	{
		is_dead = false;
		speed = 30.0f;
		changeState();
	}
}

void Ghost::changeState()
{
	if (is_dead)
	{
		sprite->changeTexture(renderer, dead_texture, position.x + width_offset, position.y + height_offset);
	}
	else if (is_vulnerable)
	{
		sprite->changeTexture(renderer, vulnerable_texture, position.x + width_offset, position.y + height_offset);
	}
	else
	{
		sprite->changeTexture(renderer, normal_texture, position.x + width_offset, position.y + height_offset);
	}
}