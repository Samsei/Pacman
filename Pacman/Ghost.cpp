#include "Ghost.h"

Ghost::Ghost(const Vector2f& entity_position, SDL_Renderer* main_renderer, const char* sprite_texture, Avatar* player, World* main_world) :
	MovableGameEntity(main_renderer, entity_position, sprite_texture),
	world(main_world),
	renderer(main_renderer)
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
		path_finder = NULL;
	}	
	if (world)
	{
		world = NULL;
	}
}

void Ghost::die()
{
	is_vulnerable = false;
	speed = 120.f;
}

void Ghost::reset(Avatar* player)
{
	setPosition(Vector2f(ghost_spawn.x * tile_size, ghost_spawn.y * tile_size));
	current_tile = Vector2f{ position.x / tile_size, position.y / tile_size };

	next_tile = path_finder->getPath(world->returnTiles(), player, current_tile, is_vulnerable, is_dead);
	entity_next_tile =
	{
		next_tile->x,
		next_tile->y
	};
}

void Ghost::update(float delta_time, Avatar* player)
{
	getNextTile(player);
	changeDirection();
	moveEntity(delta_time);
	moveSprite();
}

void Ghost::getNextTile(Avatar* player)
{
	if (isAtDestination())
	{
		next_tile = path_finder->getPath(world->returnTiles(), player, current_tile, is_vulnerable, is_dead);
		entity_next_tile = 
		{ 
			next_tile->x, 
			next_tile->y
		};
	}

	if (is_dead && current_tile == ghost_spawn)
	{
		is_dead = false;
		speed = 25.0f;
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