#include "Ghost.h"

//create the ghost, assigning world, renderer, spawn, and pacman pointers and creating a game entity
Ghost::Ghost(SDL_Renderer* main_renderer, const Vector2f& entity_position, const char* sprite_texture, Avatar* player, World* main_world, const Vector2f ghost_spawn) :
	MovableGameEntity(main_renderer, entity_position, sprite_texture, ghost_spawn),
	world(main_world),
	renderer(main_renderer),
	spawn(ghost_spawn),
	pacman(player)
{
	path_finder = new PathFinder(world->returnTiles(), player, world);
	speed = ghost_normal_speed;
	entity_next_tile = current_tile;
}

//destruct path finder and set pointers to null
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

//set the ghost to the dead state
void Ghost::setDead()
{
	is_vulnerable = false;
	is_dead = true;
	speed = ghost_dead_speed;
	sprite->changeTexture(renderer, dead_texture, position.x + width_offset, position.y + height_offset);
}

//set the ghost to its normal state
void Ghost::setNormal()
{
	is_vulnerable = false;
	is_dead = false;
	speed = ghost_normal_speed;
	sprite->changeTexture(renderer, normal_texture, position.x + width_offset, position.y + height_offset);
}

//set the ghost to the vulnerable state
void Ghost::setVulnerable()
{
	is_vulnerable = true;
	speed = ghost_vulnerable_speed;
	sprite->changeTexture(renderer, vulnerable_texture, position.x + width_offset, position.y + height_offset);
}

//update the ghosts movement and sprite
void Ghost::update(float delta_time)
{
	getNextTile();
	changeDirection();
	moveEntity(delta_time);
	moveSprite();
}

//check if the ghost is at its destination / if it has returned to spawn
void Ghost::getNextTile()
{
	if (isAtDestination())
	{
		next_tile = path_finder->getPath(pacman, current_tile, is_vulnerable, is_dead);
		setNextTile(next_tile->returnTileAsVector());
	}

	if (is_dead && current_tile == spawn)
	{
		setNormal();
	}
}