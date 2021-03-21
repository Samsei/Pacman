#include "GameEntity.h"
#include "Drawer.h"

GameEntity::GameEntity(const Vector2f& aPosition, Sprite* sprite)
:myPosition(aPosition)
,mySprite(sprite)
,myIdMarkedForDeleteFlag(false)
{
}

GameEntity::~GameEntity(void)
{
}

bool GameEntity::Intersect(GameEntity* aGameEntity)
{

	return false;	
}

void GameEntity::Draw(Drawer* aDrawer)
{
	aDrawer->Draw(mySprite, (int)myPosition.myX, (int)myPosition.myY);
}
