#include "Cherry.h"

Cherry::Cherry(Vector2f aPosition, Sprite mySprite)
	: StaticGameEntity(aPosition, &mySprite)
{
	cherrySprite = mySprite;
}

Cherry::~Cherry(void)
{
}

Sprite Cherry::ReturnSprite()
{
	return cherrySprite;
}