#include "Avatar.h"

//create the game entity for the player and assign the renderer to a pointer
Avatar::Avatar(SDL_Renderer* main_renderer, const Vector2f& avatar_position, const Vector2f player_spawn): 
	MovableGameEntity(main_renderer, avatar_position, "open_32.png", player_spawn),
	renderer(main_renderer)
{
	speed = player_speed;
}

//destruct and set pointer to null
Avatar::~Avatar(void)
{
	if (renderer)
	{
		renderer = NULL;
	}
}

//update the players movement and sprite
void Avatar::update(float delta_time)
{
	changeDirection();
	moveEntity(delta_time);
	changeSprite(delta_time);
	moveSprite();
}

//update the players input and check if the tile is a teleporter, or if the next tile is valid
void Avatar::updateInput(Vector2f next_movement, World* world)
{
	if (isAtDestination() && world->tileIsTeleport(current_tile) != Vector2f {0, 0})
	{
		teleport = { (world->tileIsTeleport(current_tile)) };
		setPosition(teleport * tile_size);
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

//change the texture of the sprite (could possibly be done using SDL animation or a spritesheet)
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

//update the timer and change the sprite based on the timer and direction
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