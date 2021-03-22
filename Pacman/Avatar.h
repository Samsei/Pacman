#ifndef AVATAR_H
#define AVATAR_H

#include "MovableGameEntity.h"
#include "Vector2f.h"
#include <string>
#include <unordered_map>

class Avatar : public MovableGameEntity
{
public:
	Avatar(SDL_Renderer*, const Vector2f&);
	~Avatar(void);

	void update(float);
	void moveAvatar(float);
	void draw(Drawer*);

private:
	void updateSprite();
	void changeSprite(float);

	const int tile_size = 22;
	float distance_to_move = 0; //added to .h instead of delcaring each frame
	float change_sprite_timer = 0;
	float sprite_open = 1;

	Vector2f destination;
	Vector2f direction ;

	SDL_Renderer* render = nullptr;

	Sprite* avatar_sprite = nullptr;
};

#endif //AVATAR_H