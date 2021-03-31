#ifndef CHERRY_H
#define CHERRY_H

#include "StaticGameEntity.h"

class Cherry : public StaticGameEntity
{
public:
	Cherry(SDL_Renderer*, Vector2f, const char* texture = "cherry.png");
	~Cherry(void);
};

#endif // CHERRY_H