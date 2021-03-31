#ifndef DOT_H
#define DOT_H

#include "GameEntity.h"

class Dot : public GameEntity
{
public:
	Dot(SDL_Renderer*, Vector2f, const char* texture = "Small_Dot_32.png");
	~Dot(void);
};

#endif // DOT_H