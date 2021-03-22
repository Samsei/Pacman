#ifndef CHERRY_H
#define CHERRY_H

#include "StaticGameEntity.h"

class Cherry : public StaticGameEntity
{
public:
	Cherry(Vector2f aPosition, Sprite mySprite);
	~Cherry(void);
	Sprite ReturnSprite();

private:
	Sprite cherrySprite;
};

#endif // CHERRY_H