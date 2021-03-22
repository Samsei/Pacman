#include "BigDot.h"

BigDot::BigDot(Vector2f aPosition, Sprite mySprite)
: StaticGameEntity(aPosition, &mySprite)
{
	dotSprite = mySprite;
}

BigDot::~BigDot(void)
{

}

Sprite BigDot::ReturnSprite()
{
	return dotSprite;
}