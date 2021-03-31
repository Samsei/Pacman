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
	Ghost(const Vector2f&, SDL_Renderer*, const char*, Avatar*, World*);
	~Ghost();

	void update(float, Avatar*);

	void die();
	void reset(Avatar*);
	void changeState();

	float speed = 25.0f;

	bool is_vulnerable = false;;
	bool is_dead = false;

private:
	void getNextTile(Avatar*);

	const char* dead_texture = "Ghost_Dead_32.png";
	const char* normal_texture = "ghost_32_pink.png";
	const char* vulnerable_texture = "Ghost_Vulnerable_32.png";
	
	const Vector2f ghost_spawn = { 13.0f, 11.0f };

	PathmapTile* next_tile = nullptr;
	PathFinder* path_finder = nullptr;
	SDL_Renderer* renderer = nullptr;
	World* world = nullptr;
};

#endif // GHOST_H