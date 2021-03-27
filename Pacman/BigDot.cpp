#include "BigDot.h"

BigDot::BigDot(Vector2f aPosition, Sprite mySprite)
: StaticGameEntity(aPosition, &mySprite)
{
	dot_sprite = mySprite;
}

BigDot::~BigDot(void)
{

}

Sprite BigDot::ReturnSprite()
{
	return dot_sprite;
}