#ifndef CHERRY_H
#define CHERRY_H

#include "GameEntity.h"

class Cherry : public GameEntity
{
public:
	Cherry(SDL_Renderer*, Vector2f, const char* texture = "cherry.png");
	~Cherry(void);
};

#endif // CHERRY_H