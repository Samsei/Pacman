#include "Avatar.h"
#include "Drawer.h"

Avatar::Avatar(SDL_Renderer* aRenderer, const Vector2f& aPosition)
: MovableGameEntity(aPosition, mySprite)
{
	mySprite = new Sprite(aRenderer, "open_32.png");
}

Avatar::~Avatar(void)
{
}

void Avatar::Update(float aTime)
{
	MoveAvatar(aTime);
}

void Avatar::MoveAvatar(float aTime)
{
	destination = Vector2f(myNextTileX * tileSize, myNextTileY * tileSize);
	direction = destination - myPosition;

	distanceToMove = aTime * 30.f;

	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		direction.Normalize();
		myPosition += direction * distanceToMove;
	}

	mySprite->MoveSprite(myPosition.myX + 220, myPosition.myY + 60);
}

void Avatar::Draw(Drawer* aDrawer)
{
	aDrawer->Draw(mySprite, myPosition.myX, myPosition.myY);
}