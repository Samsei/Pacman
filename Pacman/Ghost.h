#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"

class World;
class PathmapTile;

class Ghost : public MovableGameEntity
{
public:
	Ghost(const Vector2f&, SDL_Renderer*);
	~Ghost(void);

	void update(float, World*);
	void getNextTile();
	void findPath(float, World*);
	void moveGhost();
	void moveSprite();
	void die(World*);
	void draw(Drawer*);

	bool is_vulnerable = false;;
	bool is_dead = false;

protected:

	int desired_movement_x = 0;
	int desired_movement_y = 0;
	int next_tile_x = 0;
	int next_tile_y = 0;
	int tile_size = 22;

	float distance_to_move = 0.f;
	float speed = 30.f;

	Vector2f destination;
	Vector2f direction;

	std::list<PathmapTile*> path;

	Sprite* ghost_sprite = nullptr;
	Sprite* ghost_vulnerable_sprite = nullptr;
	Sprite* ghost_dead_sprite = nullptr;
};

#endif // GHOST_H