#include "MovableGameEntity.h"

MovableGameEntity::MovableGameEntity(const Vector2f& entity_position, Sprite* entity_sprite)
: GameEntity(entity_position, entity_sprite)
{
	current_tile_x = next_tile_x =  position.x / 22;
	current_tile_y = next_tile_y =  position.y / 22;
}

MovableGameEntity::~MovableGameEntity(void)
{
}

bool MovableGameEntity::isAtDestination()
{
	if (current_tile_x == next_tile_x && current_tile_y == next_tile_y)
	{
		return true;
	}

	return false;
}

void MovableGameEntity::setNextTile(int x, int y)
{
	next_tile_x = x;
	next_tile_y = y;
}
