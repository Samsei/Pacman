#include "Avatar.h"

Avatar::Avatar(SDL_Renderer* main_renderer, const Vector2f& avatar_position, const Vector2f player_spawn): 
	MovableGameEntity(main_renderer, avatar_position, "open_32.png", player_spawn),
	renderer(main_renderer)
{}

Avatar::~Avatar(void)
{
	if (renderer)
	{
		renderer = NULL;
	}
}

void Avatar::update(float delta_time)
{
	changeDirection();
	moveEntity(delta_time);
	changeSprite(delta_time);
	moveSprite();
}

void Avatar::updateInput(Vector2f next_movement, World* world)
{
	if (isAtDestination() && world->tileIsTeleport(current_tile) != Vector2f {0, 0})
	{
		teleport = { (world->tileIsTeleport(current_tile)) };
		setPosition(teleport);
		current_tile = position / tile_size;
		entity_next_tile = current_tile + next_movement;
	}
	else if (isAtDestination() && world->tileIsValid(current_tile + next_movement))
	{
		setNextTile(current_tile + next_movement);
		previous_movement = next_movement;
	}
	else if (world->tileIsValid(current_tile + previous_movement))
	{
		setNextTile(current_tile + previous_movement);
	}
}

void Avatar::updateSprite()
{	
	if (sprite_open)
	{
		if (direction.x == -1)
		{
			sprite->changeTexture(renderer, "open_left_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
		else if (direction.x == 1)
		{
			sprite->changeTexture(renderer, "open_right_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
		else if (direction.y == -1)
		{
			sprite->changeTexture(renderer, "open_up_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
		else if (direction.y == 1)
		{
			sprite->changeTexture(renderer, "open_down_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
	}	

	else
	{
		if (direction.x == -1)
		{
			sprite->changeTexture(renderer, "closed_left_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
		else if (direction.x == 1)
		{
			sprite->changeTexture(renderer, "closed_right_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
		else if (direction.y == -1)
		{
			sprite->changeTexture(renderer, "closed_up_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
		else if (direction.y == 1)
		{
			sprite->changeTexture(renderer, "closed_down_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
	}
}

void Avatar::changeSprite(float delta_time)
{
	timer += delta_time;
	if (timer >= sprite_change_timer)
	{
		sprite_open = !sprite_open;
		timer = 0;
	}
	updateSprite();
}