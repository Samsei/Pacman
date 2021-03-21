#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"

class World;
class PathmapTile;

class Ghost : public MovableGameEntity
{
public:
	Ghost(const Vector2f& aPosition, SDL_Renderer* aRenderer);
	~Ghost(void);

	void Update(float aTime, World* aWorld);

	bool myIsClaimableFlag = false;;
	bool myIsDeadFlag = false;

	void Die(World* aWorld);

	void Draw(Drawer* aDrawer);

protected:

	int myDesiredMovementX = 0;
	int myDesiredMovementY = 0;

	std::list<PathmapTile*> myPath;

	Sprite* ghostSprite ;
	Sprite* ghostVulnerableSprite;
	Sprite* ghostDeadSprite;
};

#endif // GHOST_H