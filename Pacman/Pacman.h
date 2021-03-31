#ifndef PACMAN_H
#define PACMAN_H

#include <vector>
#include <sstream>

#include "Avatar.h"
#include "Ghost.h"

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

	bool checkEndGameCondition();
	bool updateInput();

	void checkTimers(float);
	void drawText();
	void hitGhost();
	void updateScore();

	float ghost_timer = 0.0f;
	float immortal_timer = 0.0f;
	float time_to_next_update = 0.0f;

	int fps = 0;	
	int lives = 3;
	int score = 0;

	const int tile_size = 22;

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	Vector2f next_movement = { -1.0f, 0.0f };

	const Vector2f ghost_spawn = { 13.0f, 13.0f };
	const Vector2f player_spawn = { 13.0f, 22.0f };

	std::vector<Ghost*> ghosts;
	
	Avatar* player = nullptr;
	Drawer* renderer = nullptr;
	Ghost* ghost = nullptr;
	Sprite* player_sprite = nullptr;
	World* world = nullptr;
};

#endif // PACMAN_H