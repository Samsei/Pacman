#ifndef PACMAN_H
#define PACMAN_H

#include "Vector2f.h"
#include "Drawer.h"
#include "SDL.h"

#include "Avatar.h"
#include "World.h"
#include "Ghost.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

struct SDL_Surface;
class Drawer;
class Avatar;
class World;
class Ghost;

class Pacman
{
public:
	static Pacman* Create(Drawer*);
	~Pacman(void);

	bool update(float);	
	bool draw();

private:
	Pacman(Drawer*);
	bool init();
	bool updateInput();
	void movePlayer();
	bool checkEndGameCondition();
	void updateScore();
	void hitGhost();
	void checkGhostTimer(float);
	void drawText();


	float time_to_next_update;
	float ghost_timer;

	int next_tile_x;
	int next_tile_y; //added to .h instead of initializing every frame

	int lives;
	int score;
	int fps;

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	Vector2f next_movement;

	Avatar* player;
	Ghost* ghost;
	World* world;
	Drawer* renderer;
	Sprite* player_sprite;
};

#endif // PACMAN_H