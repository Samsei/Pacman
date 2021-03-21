#include "Avatar.h"
#include "Drawer.h"

Avatar::Avatar(SDL_Renderer* aRenderer, const Vector2f& aPosition, Sprite* avatarSprite)
: MovableGameEntity(aPosition, avatarSprite)
{
	mySprite = avatarSprite;
}

Avatar::~Avatar(void)
{
}

void Avatar::Update(float aTime)
{
	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	Vector2f direction = destination - myPosition;

	distanceToMove = aTime * 30.f;

	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
		mySprite->MoveSprite(myPosition.myX + 220, myPosition.myY + 60);
	}
	else
	{
		direction.Normalize();
		myPosition += direction * distanceToMove;
		mySprite->MoveSprite(myPosition.myX + 220, myPosition.myY + 60);
	}
}

void Avatar::Draw(Drawer* aDrawer)
{
	aDrawer->Draw(mySprite, myPosition.myX, myPosition.myY);
}