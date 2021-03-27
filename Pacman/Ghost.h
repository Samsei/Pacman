#ifndef GHOST_H
#define GHOST_H

#include <list>

#include "World.h"
#include "PathmapTile.h"
#include "Drawer.h"
#include "MovableGameEntity.h"
#include "PathFinder.h"

class World;
class PathmapTile;

class Ghost : public MovableGameEntity
{
public:
	Ghost(const Vector2f&, SDL_Renderer*, const char*, int);

	void update(float, World*, Vector2f);
	void getNextTile();
	void findPath(float, World*, Vector2f);
	void moveGhost();
	void moveSprite();
	void die(World*);
	void draw(Drawer*);
	void changeMovementDirection();

	bool is_vulnerable = false;;
	bool is_dead = false;

protected:
	int desired_movement_x = 0;
	int desired_movement_y = -1;
	int next_tile_x = 0;
	int next_tile_y = 0;
	int tile_size = 22;
	int ghost_intelligence = 0;

	float distance_to_move = 0.f;
	float speed = 30.f;

	Vector2f destination = { 0, 0 };
	Vector2f direction = { 0, 0 };

	std::list<PathmapTile*> path;

	PathmapTile* nextTile = nullptr;
	PathFinder* pathFinder = nullptr;

	Sprite* ghost_sprite = nullptr;
	Sprite* ghost_vulnerable_sprite = nullptr;
	Sprite* ghost_dead_sprite = nullptr;
};

#endif // GHOST_H