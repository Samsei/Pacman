#include "Ghost.h"

Ghost::Ghost(const Vector2f& entity_position, SDL_Renderer* main_renderer, const char* sprite, int intelligence, Avatar* player, World* main_world) : 
	MovableGameEntity(entity_position, ghost_sprite),
    world(main_world)
{
	ghost_sprite = new Sprite(main_renderer, sprite, 0, 0);
	ghost_vulnerable_sprite = new Sprite(main_renderer, "Ghost_Vulnerable_32.png", 0, 0);
	ghost_dead_sprite = new Sprite(main_renderer, "Ghost_Dead_32.png", 0, 0);

	pathFinder = new PathFinder(player, intelligence, world);
}

void Ghost::die()
{
	path.clear();
	speed = 120.f;
}

void Ghost::update(float delta_time)
{
	getNextTile();
	findPath(delta_time);
	moveGhost();
}

void Ghost::findPath(float delta_time)
{
	if (isAtDestination())
	{
		if (world->tileIsValid(next_tile.x, next_tile.y))
		{
			setNextTile(next_tile.x, next_tile.y);
		}
		else
		{
			changeMovementDirection();
			is_dead = false;
			speed = 30.0f;
		}
	}

	destination = Vector2f(entity_next_tile.x * tile_size, entity_next_tile.y * tile_size);
	direction = destination - position;

	distance_to_move = delta_time * speed;
}

void Ghost::changeMovementDirection()
{
	if (desired_movement.x == 1)
	{
		desired_movement.x = 0;
		desired_movement.y = 1;
	}
	else if (desired_movement.y == 1)
	{
		desired_movement.x = -1;
		desired_movement.y = 0;
	}
	else if (desired_movement.x == -1)
	{
		desired_movement.x = 0;
		desired_movement.y = -1;
	}
	else
	{
		desired_movement.x = 1;
		desired_movement.y = 0;
	}
}

void Ghost::getNextTile()
{
	next_tile = { getCurrentTile().x + desired_movement.x, getCurrentTile().y + desired_movement.y };
}

void Ghost::moveGhost()
{
	if (distance_to_move > direction.Length())
	{
		position = destination;
		current_tile = { entity_next_tile.x, entity_next_tile.y };
	}
	else
	{
		direction.Normalize();
		position += direction * distance_to_move;
	}

	moveSprite();
}

void Ghost::moveSprite()
{
	if (is_dead)
	{
		ghost_dead_sprite->moveSprite(position.x + 220, position.y + 60);
	}
	else if (is_vulnerable)
	{
		ghost_vulnerable_sprite->moveSprite(position.x + 220, position.y + 60);
	}
	else
	{
		ghost_sprite->moveSprite(position.x + 220, position.y + 60);
	}
}

void Ghost::draw(Drawer* renderer)
{
	if (is_dead)
	{
		renderer->draw(ghost_dead_sprite, position.x, position.y);

	}
	else if (is_vulnerable)
	{
		renderer->draw(ghost_vulnerable_sprite, position.x, position.y);
	}
	else
	{
		renderer->draw(ghost_sprite, position.x, position.y);
	}
}