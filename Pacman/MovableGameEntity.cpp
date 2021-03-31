#include "MovableGameEntity.h"

MovableGameEntity::MovableGameEntity(SDL_Renderer* main_renderer, const Vector2f& entity_position, const char* entity_image)
: GameEntity(main_renderer, entity_position, entity_image)
{
	current_tile.x = entity_next_tile.x =  position.x / 22;
	current_tile.y = entity_next_tile.y =  position.y / 22;
}

MovableGameEntity::~MovableGameEntity(void)
{}

void MovableGameEntity::changeDirection()
{
	destination = Vector2f(entity_next_tile.x * tile_size, entity_next_tile.y * tile_size);
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

void MovableGameEntity::moveSprite()
{
	sprite->moveSprite(position.x + width_offset, position.y + height_offset);
}

void MovableGameEntity::setNextTile(float x, float y)
{
	entity_next_tile = { x, y };
}
