#include "Ghost.h"
#include "World.h"
#include "PathmapTile.h"
#include "Drawer.h"

Ghost::Ghost(const Vector2f& aPosition, SDL_Renderer* aRenderer)
: MovableGameEntity(aPosition, ghostSprite)
{
	myIsClaimableFlag = false;
	myIsDeadFlag = false;

	myDesiredMovementX = 0;
	myDesiredMovementY = -1;

	ghostSprite = new Sprite(aRenderer, "ghost_32.png", 0, 0);
	ghostVulnerableSprite = new Sprite(aRenderer, "Ghost_Vulnerable_32.png", 0, 0);
	ghostDeadSprite = new Sprite(aRenderer, "Ghost_Dead_32.png", 0, 0);
}

Ghost::~Ghost(void)
{
}

void Ghost::Die(World* aWorld)
{
	myPath.clear();
	aWorld->GetPath(myCurrentTileX, myCurrentTileY, 13, 13, myPath);
}

void Ghost::Update(float aTime, World* aWorld)
{
	float speed = 30.f;
	int nextTileX = GetCurrentTileX() + myDesiredMovementX;
	int nextTileY = GetCurrentTileY() + myDesiredMovementY;

	if (myIsDeadFlag)
		speed = 120.f;

	if (IsAtDestination())
	{
		if (!myPath.empty())
		{
			PathmapTile* nextTile = myPath.front();
			myPath.pop_front();
			SetNextTile(nextTile->myX, nextTile->myY);
		}
		else if (aWorld->TileIsValid(nextTileX, nextTileY))
		{
			SetNextTile(nextTileX, nextTileY);
		}
		else
		{
			if (myDesiredMovementX == 1)
			{
				myDesiredMovementX = 0;
				myDesiredMovementY = 1;
			} else if (myDesiredMovementY == 1)
			{
				myDesiredMovementX = -1;
				myDesiredMovementY = 0;			
			} else if (myDesiredMovementX == -1)
			{
				myDesiredMovementX = 0;
				myDesiredMovementY = -1;
			} else
			{
				myDesiredMovementX = 1;
				myDesiredMovementY = 0;
			}

			myIsDeadFlag = false;
		}
	}

	int tileSize = 22;
	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	Vector2f direction = destination - myPosition;

	float distanceToMove = aTime * speed;

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

	ghostSprite->MoveSprite(myPosition.myX + 220, myPosition.myY + 60);
}

void Ghost::Draw(Drawer* aDrawer)
{
	if (myIsDeadFlag)
		aDrawer->Draw(ghostDeadSprite, (int)myPosition.myX, (int)myPosition.myY);
	else if (myIsClaimableFlag)
		aDrawer->Draw(ghostVulnerableSprite, (int)myPosition.myX, (int)myPosition.myY);
	else
		aDrawer->Draw(ghostSprite, (int)myPosition.myX, (int)myPosition.myY);
}
