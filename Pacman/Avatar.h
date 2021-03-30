#ifndef AVATAR_H
#define AVATAR_H

#include "MovableGameEntity.h"
#include "Drawer.h"
#include "World.h"

class Avatar : public MovableGameEntity
{
public:
	Avatar(SDL_Renderer*, const Vector2f&);
	~Avatar(void);

	void reset();
	void update(float);
	void moveAvatar(float);
	void updateInput(Vector2f, World*);
	void draw(Drawer*);

private:
	void updateSprite();
	void changeSprite(float);

	const int height_offset = 60;
	const int tile_size = 22;
	const int width_offset = 220;

	const float speed = 30.0f;
	const float sprite_timer = 0.365f;

	float change_sprite_timer = 0;
	float distance_to_move = 0; //added to .h instead of delcaring each frame

	bool sprite_open = true;;

	Vector2f destination = { 0.0f, 0.0f };
	Vector2f direction = { 0.0f, 0.0f };
	Vector2f previous_movement = { 0.0f, 0.0f };

	const Vector2f player_spawn = { 13.0f, 22.0f };

	SDL_Renderer* render = nullptr;	
	Sprite* avatar_sprite = nullptr;
};

#endif //AVATAR_H