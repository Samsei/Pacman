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
	static Pacman* Create(Drawer* aDrawer);
	~Pacman(void);

	bool Update(float aTime);	
	bool Draw();

private:
	Pacman(Drawer* aDrawer);
	bool Init();
	bool UpdateInput();
	void MoveAvatar();
	bool CheckEndGameCondition();
	void UpdateScore();
	void HitGhost();
	void CheckGhostTimer(float aTime);
	void DrawText();

	Drawer* myDrawer;

	float myTimeToNextUpdate;
	float myGhostGhostCounter;

	int nextTileX;
	int nextTileY; //added to .h instead of initializing every frame

	int myLives;
	int myScore;
	int myFps;

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	Vector2f myNextMovement;

	Avatar* myAvatar;
	Ghost* myGhost;
	World* myWorld;

	Sprite* avatarSprite;
};

#endif // PACMAN_H