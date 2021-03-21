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
	GetNextTile();

	FindPath(aTime, aWorld);

	MoveGhost();
}

void Ghost::FindPath(float aTime, World* aWorld)
{
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
			}
			else if (myDesiredMovementY == 1)
			{
				myDesiredMovementX = -1;
				myDesiredMovementY = 0;
			}
			else if (myDesiredMovementX == -1)
			{
				myDesiredMovementX = 0;
				myDesiredMovementY = -1;
			}
			else
			{
				myDesiredMovementX = 1;
				myDesiredMovementY = 0;
			}

			myIsDeadFlag = false;
			speed = 30.0f;
		}
	}

	destination = Vector2f(myNextTileX * tileSize, myNextTileY * tileSize);
	direction = destination - myPosition;

	distanceToMove = aTime * speed;
}

void Ghost::GetNextTile()
{
	nextTileX = GetCurrentTileX() + myDesiredMovementX;
	nextTileY = GetCurrentTileY() + myDesiredMovementY;
}

void Ghost::MoveGhost()
{
	if (myIsDeadFlag)
	{
		speed = 120.f;
	}

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

	MoveSprite();
}

void Ghost::MoveSprite()
{
	if (myIsDeadFlag)
	{
		ghostDeadSprite->MoveSprite(myPosition.myX + 220, myPosition.myY + 60);
	}
	else if (myIsClaimableFlag)
	{
		ghostVulnerableSprite->MoveSprite(myPosition.myX + 220, myPosition.myY + 60);
	}
	else
	{
		ghostSprite->MoveSprite(myPosition.myX + 220, myPosition.myY + 60);
	}
}

void Ghost::Draw(Drawer* aDrawer)
{
	if (myIsDeadFlag)
	{
		aDrawer->Draw(ghostDeadSprite, (int)myPosition.myX, (int)myPosition.myY);

	}
	else if (myIsClaimableFlag)
	{
		aDrawer->Draw(ghostVulnerableSprite, (int)myPosition.myX, (int)myPosition.myY);
	}
	else
	{
		aDrawer->Draw(ghostSprite, (int)myPosition.myX, (int)myPosition.myY);
	}
}