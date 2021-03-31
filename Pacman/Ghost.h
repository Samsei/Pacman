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
	Ghost(SDL_Renderer*, const Vector2f&, const char*, Avatar*, World*, const Vector2f);
	~Ghost();

	void update(float);

	void setDead();
	void setNormal();
	void setVulnerable();
	void changeState();

	bool is_vulnerable = false;;
	bool is_dead = false;

private:
	void getNextTile();

	const char* dead_texture = "Ghost_Dead_32.png";
	const char* normal_texture = "ghost_32_pink.png";
	const char* vulnerable_texture = "Ghost_Vulnerable_32.png";

	Vector2f spawn = { 0.0f, 0.0f };
	
	Avatar* pacman = nullptr;
	PathmapTile* next_tile = nullptr;
	PathFinder* path_finder = nullptr;
	SDL_Renderer* renderer = nullptr;
	World* world = nullptr;
};

#endif // GHOST_H