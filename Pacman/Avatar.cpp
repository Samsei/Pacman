#include "Avatar.h"

Avatar::Avatar(SDL_Renderer* main_renderer, const Vector2f& avatar_position): 
	MovableGameEntity(main_renderer, avatar_position, "open_32.png"),
	render(main_renderer)
{}

Avatar::~Avatar(void)
{}

void Avatar::reset()
{
	setPosition(Vector2f(player_spawn.x * tile_size, player_spawn.y * tile_size));
	current_tile = Vector2f{ position.x / tile_size, position.y / tile_size };
	entity_next_tile = current_tile;
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
	if (isAtDestination() && world->tileIsTeleport(getCurrentTile().x, getCurrentTile().y) != Vector2f {0, 0})
	{
		teleport = { (world->tileIsTeleport(getCurrentTile().x, getCurrentTile().y)) };
		setPosition(teleport);
		current_tile = Vector2f{ position.x / tile_size, position.y / tile_size };
		entity_next_tile = current_tile + next_movement;
	}
	else if (isAtDestination() && world->tileIsValid(getCurrentTile().x + next_movement.x, getCurrentTile().y + next_movement.y))
	{
		entity_next_tile =
		{
			getCurrentTile().x + next_movement.x,
			getCurrentTile().y + next_movement.y
		};

		setNextTile(entity_next_tile.x, entity_next_tile.y);
		previous_movement = next_movement;
	}
	else if (world->tileIsValid(getCurrentTile().x + previous_movement.x, getCurrentTile().y + previous_movement.y))
	{
		entity_next_tile =
		{
			getCurrentTile().x + previous_movement.x,
			getCurrentTile().y + previous_movement.y
		};

		setNextTile(entity_next_tile.x, entity_next_tile.y);
	}
}

void Avatar::updateSprite()
{	
	if (sprite_open)
	{
		if (direction.x == -1)
		{
			sprite->changeTexture(render, "open_left_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
		else if (direction.x == 1)
		{
			sprite->changeTexture(render, "open_right_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
		else if (direction.y == -1)
		{
			sprite->changeTexture(render, "open_up_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
		else if (direction.y == 1)
		{
			sprite->changeTexture(render, "open_down_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
	}	

	else
	{
		if (direction.x == -1)
		{
			sprite->changeTexture(render, "closed_left_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
		else if (direction.x == 1)
		{
			sprite->changeTexture(render, "closed_right_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
		else if (direction.y == -1)
		{
			sprite->changeTexture(render, "closed_up_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
		else if (direction.y == 1)
		{
			sprite->changeTexture(render, "closed_down_32.png", position.x + width_offset, position.y + height_offset);
			return;
		}
	}
}

void Avatar::changeSprite(float delta_time)
{
	change_sprite_timer += delta_time;
	if (change_sprite_timer >= sprite_timer)
	{
		sprite_open = !sprite_open;
		change_sprite_timer = 0;
	}
	updateSprite();
}