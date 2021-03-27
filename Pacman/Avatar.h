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

	void update(float, Vector2f);
	void moveAvatar(float);
	void updateInput(Vector2f, World*);
	void draw(Drawer*);

private:
	void updateSprite();
	void changeSprite(float);

	const int tile_size = 22;

	const float sprite_timer = 0.365f;
	const float speed = 30.0f;
	float distance_to_move = 0; //added to .h instead of delcaring each frame
	float change_sprite_timer = 0;
	float sprite_open = 1;

	Vector2f destination = { 0.0f, 0.0f };
	Vector2f direction = { 0.0f, 0.0f };

	SDL_Renderer* render = nullptr;
	
	Sprite* avatar_sprite = nullptr;
};

#endif //AVATAR_H