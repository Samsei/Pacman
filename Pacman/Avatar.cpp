#include "Avatar.h"
#include "Drawer.h"
#include "Pacman.h"

Avatar::Avatar(SDL_Renderer* aRenderer, const Vector2f& aPosition)
	: MovableGameEntity(aPosition, mySprite),
	myRenderer(aRenderer)
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

	PlaceHoldName(aTime);
	UpdateSprite();

	mySprite->MoveSprite(myPosition.myX + 220, myPosition.myY + 60);
}

void Avatar::UpdateSprite()
{
	if (direction.myX == -1 && spriteOpen == -1)
	{
		mySprite->ChangeTexture(myRenderer, "closed_left_32.png", myPosition.myX + 220, myPosition.myY + 60);
	}
	else if (direction.myX == -1 && spriteOpen == 1)
	{
		mySprite->ChangeTexture(myRenderer, "open_left_32.png", myPosition.myX + 220, myPosition.myY + 60);
	}

	else if (direction.myX == 1 && spriteOpen == -1)
	{
		mySprite->ChangeTexture(myRenderer, "closed_right_32.png", myPosition.myX + 220, myPosition.myY + 60);
	}
	else if (direction.myX == 1 && spriteOpen == 1)
	{
		mySprite->ChangeTexture(myRenderer, "open_right_32.png", myPosition.myX + 220, myPosition.myY + 60);
	}

	else if (direction.myY == -1 && spriteOpen == -1)
	{
		mySprite->ChangeTexture(myRenderer, "closed_up_32.png", myPosition.myX + 220, myPosition.myY + 60);
	}
	else if (direction.myY == -1 && spriteOpen == 1)
	{
		mySprite->ChangeTexture(myRenderer, "open_up_32.png", myPosition.myX + 220, myPosition.myY + 60);
	}

	else if (direction.myY == 1 && spriteOpen == -1)
	{
		mySprite->ChangeTexture(myRenderer, "closed_down_32.png", myPosition.myX + 220, myPosition.myY + 60);
	}
	else if (direction.myY == 1 && spriteOpen == 1)
	{
		mySprite->ChangeTexture(myRenderer, "open_down_32.png", myPosition.myX + 220, myPosition.myY + 60);
	}
}

void Avatar::PlaceHoldName(float aTime)
{
	changeSpriteTime += aTime;
	if (changeSpriteTime >= 0.35)
	{
		spriteOpen *= -1;
		changeSpriteTime = 0;
	}
}

void Avatar::Draw(Drawer* aDrawer)
{
	aDrawer->Draw(mySprite, myPosition.myX, myPosition.myY);
}