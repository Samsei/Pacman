#include "GameEntity.h"

//create the sprite for the game entity, and assign the position of the entity
GameEntity::GameEntity(SDL_Renderer* main_renderer, const Vector2f& entity_position, const char* entity_image):
	position(entity_position)
{
	sprite = new Sprite(main_renderer, entity_image, entity_position.x + width_offset, entity_position.y + height_offset);
}

//deconstruct sprite and set pointer to null
GameEntity::~GameEntity(void)
{
	if (sprite)
	{
		delete sprite;
		sprite = NULL;
	}
}

//check if the player is intersecting with the gameentity
bool GameEntity::intersect(Vector2f entity_position)
{
	if (entity_position == position)
	{
		return true;
	}
	return false;
}

//draw the game entity
void GameEntity::draw(Drawer* renderer)
{
	renderer->draw(sprite);
}