#include "Dot.h"
#include "Sprite.h"
Dot::Dot(Vector2f aPosition, Sprite mySprite)
: StaticGameEntity(aPosition, &mySprite)
{
	dotSprite = mySprite;
}

Dot::~Dot(void)
{

}

Sprite Dot::ReturnSprite()
{
	return dotSprite;
}