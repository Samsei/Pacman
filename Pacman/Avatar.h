#ifndef AVATAR_H
#define AVATAR_H

#include "MovableGameEntity.h"
#include "Drawer.h"
#include "World.h"

class Avatar : public MovableGameEntity
{
public:
	Avatar(SDL_Renderer*, const Vector2f&, const Vector2f);
	~Avatar(void);

	void update(float);
	void updateInput(Vector2f, World*);

private:
	void updateSprite();
	void changeSprite(float);

	const float sprite_change_timer = 0.365f;

	float timer = 0.0f;

	int player_speed = 30;

	bool sprite_open = true;;
	
	Vector2f previous_movement = { 0.0f, 0.0f };
	Vector2f teleport = { 0.0f, 0.0f };

	SDL_Renderer* renderer = nullptr;	
};

#endif //AVATAR_H