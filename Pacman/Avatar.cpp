#include "Avatar.h"

Avatar::Avatar(SDL_Renderer* main_renderer, const Vector2f& avatar_position): 
	MovableGameEntity(avatar_position, avatar_sprite),
	render(main_renderer)
{
	avatar_sprite = new Sprite(main_renderer, "open_32.png");
}

Avatar::~Avatar(void)
{
	delete avatar_sprite;

	avatar_sprite = NULL;
}

void Avatar::update(float delta_time, Vector2f next_movement)
{
	moveAvatar(delta_time);
	changeSprite(delta_time);
	updateSprite();
}

void Avatar::moveAvatar(float delta_time)
{
	destination = Vector2f(entity_next_tile.x * tile_size, entity_next_tile.y * tile_size);
	direction = destination - position;

	distance_to_move = delta_time * speed;

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
}

void Avatar::updateInput(Vector2f next_movement, World* world)
{
	if (isAtDestination() && world->tileIsValid(getCurrentTile().x + next_movement.x, getCurrentTile().y + next_movement.y))  //unnested if statement
	{
		entity_next_tile = { getCurrentTile().x + next_movement.x,  getCurrentTile().y + next_movement.y };
		setNextTile(entity_next_tile.x, entity_next_tile.y);
	}
}

void Avatar::updateSprite()
{
	if (sprite_open == -1)
	{
		if (direction.x == -1)
		{
			avatar_sprite->changeTexture(render, "closed_left_32.png", position.x + 220, position.y + 60);
			return;
		}
		
		else if (direction.y == -1)
		{
			avatar_sprite->changeTexture(render, "closed_up_32.png", position.x + 220, position.y + 60);
			return;
		}

		else if (direction.x == 1)
		{
			avatar_sprite->changeTexture(render, "closed_right_32.png", position.x + 220, position.y + 60);
			return;
		}
		
		else if (direction.y == 1)
		{
			avatar_sprite->changeTexture(render, "closed_down_32.png", position.x + 220, position.y + 60);
			return;
		}		
	}
	
	else
	{
		if (direction.x == -1)
		{
			avatar_sprite->changeTexture(render, "open_left_32.png", position.x + 220, position.y + 60);
			return;
		}

		else if (direction.y == -1)
		{
			avatar_sprite->changeTexture(render, "open_up_32.png", position.x + 220, position.y + 60);
			return;
		}
		else if (direction.x == 1)
		{
			avatar_sprite->changeTexture(render, "open_right_32.png", position.x + 220, position.y + 60);
			return;
		}
		else if (direction.y == 1)
		{
			avatar_sprite->changeTexture(render, "open_down_32.png", position.x + 220, position.y + 60);
			return;
		}
	}	

	avatar_sprite->moveSprite(position.x + 220, position.y + 60);
}

void Avatar::changeSprite(float delta_time)
{
	change_sprite_timer += delta_time;
	if (change_sprite_timer >= sprite_timer)
	{
		sprite_open *= -1;
		change_sprite_timer = 0;
	}
}

void Avatar::draw(Drawer* renderer)
{
	renderer->draw(avatar_sprite, position.x, position.y);
}