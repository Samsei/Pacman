#ifndef BIGDOT_H
#define BIGDOT_H

#include "GameEntity.h"

class BigDot : public GameEntity
{
public:
	BigDot(SDL_Renderer*, Vector2f, const char* texture = "Big_Dot_32.png");
	~BigDot(void);
};

#endif // BIGDOT_H