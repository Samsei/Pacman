#include "Dot.h"

Dot::Dot(Vector2f aPosition, Sprite mySprite)
: StaticGameEntity(aPosition, &mySprite)
{
	dot_sprite = mySprite;
}

Dot::~Dot(void)
{

}

Sprite Dot::ReturnSprite()
{
	return dot_sprite;
}