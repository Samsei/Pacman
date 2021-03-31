#ifndef BIGDOT_H
#define BIGDOT_H

#include "StaticGameEntity.h"

class BigDot : public StaticGameEntity
{
public:
	BigDot(SDL_Renderer*, Vector2f, const char* texture = "Big_Dot_32.png");
	~BigDot(void);
};

#endif // BIGDOT_H