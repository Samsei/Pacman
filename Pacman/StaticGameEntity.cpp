#include "StaticGameEntity.h"

//create the static entity as a game entity and pass the renderer, position and image path
StaticGameEntity::StaticGameEntity(SDL_Renderer* main_renderer, Vector2f entity_position, const char* entity_sprite)
	: GameEntity(main_renderer, entity_position, entity_sprite)
{
}

StaticGameEntity::~StaticGameEntity(void)
{}