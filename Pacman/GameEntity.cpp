#include "GameEntity.h"

GameEntity::GameEntity(SDL_Renderer* main_renderer, const Vector2f& entity_position, const char* entity_image):
	position(entity_position)
{
	sprite = new Sprite(main_renderer, entity_image, entity_position.x + width_offset, entity_position.y + height_offset);
}

GameEntity::~GameEntity(void)
{

}

bool GameEntity::intersect(Vector2f entity_position)
{
	if (entity_position == position)
	{
		return true;
	}
	return false;
}

void GameEntity::draw(Drawer* renderer)
{
	renderer->draw(sprite);
}