#ifndef AVATAR_H
#define AVATAR_H

#include "MovableGameEntity.h"
#include "Vector2f.h"
#include <string>

class Avatar : public MovableGameEntity
{
public:
	Avatar(SDL_Renderer* aRenderer, const Vector2f& aPosition);
	~Avatar(void);

	void Update(float aTime);
	void MoveAvatar(float aTime);
	void Draw(Drawer* aDrawer);
	void UpdateSprite();
	void PlaceHoldName(float aTime);
private:

	const int tileSize = 22;
	float distanceToMove = 0; //added to .h instead of delcaring each frame

	float changeSpriteTime = 0;

	int spriteOpen = 1;

	Vector2f destination;
	Vector2f direction ;

	SDL_Renderer* myRenderer;

	Sprite* mySprite;
};

#endif //AVATAR_H