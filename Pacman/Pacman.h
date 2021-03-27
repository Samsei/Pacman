#ifndef PACMAN_H
#define PACMAN_H

#include <vector>
#include <sstream>

#include "Avatar.h"
#include "Ghost.h"
#include "World.h"

struct SDL_Surface;
class Drawer;
class Sprite;
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
	bool checkEndGameCondition();

	void movePlayer();
	void updateScore();
	void hitGhost();
	void checkGhostTimer(float);
	void drawText();

	float time_to_next_update = 0;
	float ghost_timer = 0;

	int entity_next_tile_x = 0;
	int entity_next_tile_y = 0;
	int lives = 0;
	int score = 0;
	int fps = 0;
	int intelligence = 0;

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	Vector2f next_movement = { 0, 0 };

	Avatar* player = nullptr;

	std::vector<Ghost*> ghosts;
	std::list<const char*> ghost_sprite_paths = {"ghost_32_red.png", "ghost_32_pink.png", "ghost_32_cyan.png", "ghost_32_orange.png"};

	Ghost* ghost = nullptr;
	World* world = nullptr;
	Drawer* renderer = nullptr;
	Sprite* player_sprite = nullptr;
};

#endif // PACMAN_H