#include "GameEntity.h"

GameEntity::GameEntity(const Vector2f& entity_position, Sprite* entity_sprite):
	position(entity_position),
	sprite(entity_sprite)
{
}

GameEntity::~GameEntity(void)
{

}

bool GameEntity::intersect(GameEntity* aGameEntity)
{
	return false;	
}

void GameEntity::draw(Drawer* renderer)
{
	renderer->draw(sprite, (int)position.x, (int)position.y);
}
