#ifndef AVATAR_H
#define AVATAR_H

#include "MovableGameEntity.h"
#include "Vector2f.h"

class Avatar : public MovableGameEntity
{
public:
	Avatar(SDL_Renderer* aRenderer, const Vector2f& aPosition);
	~Avatar(void);

	void Update(float aTime);
	void MoveAvatar(float aTime);
	void Draw(Drawer* aDrawer);

private:

	const int tileSize = 22;
	float distanceToMove; //added to .h instead of delcaring each frame

	Vector2f destination;
	Vector2f direction ;

	Sprite* mySprite;
};

#endif //AVATAR_H