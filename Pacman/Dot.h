#ifndef DOT_H
#define DOT_H

#include "StaticGameEntity.h"

class Dot : public StaticGameEntity
{
public:
	Dot(Vector2f aPosition, Sprite mySprite);
	~Dot(void);

	Sprite ReturnSprite();

private:
	Sprite dot_sprite;
};

#endif // DOT_H