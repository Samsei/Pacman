#ifndef GHOST_H
#define GHOST_H

#include <list>

#include "PathmapTile.h"
#include "Drawer.h"
#include "MovableGameEntity.h"
#include "PathFinder.h"

class World;
class PathmapTile;

class Ghost : public MovableGameEntity
{
public:
	Ghost(const Vector2f&, SDL_Renderer*, const char*, int, Avatar*, World*);

	void update(float, Avatar*);
	void draw(Drawer*);

	void die();
	void reset(Avatar*);

	bool is_vulnerable = false;;
	bool is_dead = false;

private:
	void changeMovementDirection();
	void getNextTile(Avatar*);
	void moveGhost();
	void moveSprite();

	float distance_to_move = 0.0f;
	float speed = 25.0f;

	const int height_offset = 60;
	const int tile_size = 22;
	const int width_offset = 220;

	Vector2f desired_movement = { 0.0f, 0.0f };
	Vector2f destination = { 0.0f, 0.0f };
	Vector2f direction = { 0.0f, 0.0f };
	
	const Vector2f ghost_spawn = { 13.0f, 11.0f };

	PathmapTile* next_tile = nullptr;
	PathFinder* path_finder = nullptr;
	Sprite* ghost_dead_sprite = nullptr;
	Sprite* ghost_sprite = nullptr;
	Sprite* ghost_vulnerable_sprite = nullptr;	
	World* world = nullptr;
};

#endif // GHOST_H