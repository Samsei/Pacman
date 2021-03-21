#ifndef DOT_H
#define DOT_H

#include "StaticGameEntity.h"
#include "Vector2f.h"

class Dot : public StaticGameEntity
{
public:
	Dot(Vector2f aPosition, Sprite mySprite);
	~Dot(void);
	Sprite ReturnSprite();

private:
	Sprite dotSprite;
};

#endif // DOT_H