#include "MovableGameEntity.h"

MovableGameEntity::MovableGameEntity(const Vector2f& entity_position, Sprite* entity_sprite)
: GameEntity(entity_position, entity_sprite)
{
	current_tile.x = entity_next_tile.x =  position.x / 22;
	current_tile.y = entity_next_tile.y =  position.y / 22;
}

MovableGameEntity::~MovableGameEntity(void)
{
}

bool MovableGameEntity::isAtDestination()
{
	if (current_tile.x == entity_next_tile.x && current_tile.y == entity_next_tile.y)
	{
		return true;
	}

	return false;
}

void MovableGameEntity::setNextTile(float x, float y)
{
	entity_next_tile = { x, y };
}
