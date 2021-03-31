#include "MovableGameEntity.h"

MovableGameEntity::MovableGameEntity(SDL_Renderer* main_renderer, const Vector2f& entity_position, const char* entity_image, const Vector2f entity_spawn)
	: GameEntity(main_renderer, entity_position, entity_image),
	spawn(entity_spawn)
{
	current_tile = entity_next_tile =  position / tile_size;
}

MovableGameEntity::~MovableGameEntity(void)
{}

void MovableGameEntity::changeDirection()
{
	destination = entity_next_tile * tile_size;
	direction = destination - position;
}

void MovableGameEntity::moveEntity(float delta_time)
{
	distance_to_move = delta_time * speed;

	if (distance_to_move > direction.Length())
	{
		position = destination;
		current_tile = entity_next_tile;
	}
	else
	{
		direction.Normalize();
		position += direction * distance_to_move;
	}
}

bool MovableGameEntity::isAtDestination()
{
	if (current_tile == entity_next_tile)
	{
		return true;
	}

	return false;
}

void MovableGameEntity::reset()
{
	setPosition(spawn * tile_size);
	current_tile = position / tile_size;
	entity_next_tile = current_tile;
}

void MovableGameEntity::moveSprite()
{
	sprite->moveSprite(position.x + width_offset, position.y + height_offset);
}

void MovableGameEntity::setNextTile(Vector2f next_tile)
{
	entity_next_tile = next_tile;
}