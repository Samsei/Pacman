#ifndef DOT_H
#define DOT_H

#include "StaticGameEntity.h"

class Dot : public StaticGameEntity
{
public:
	Dot(SDL_Renderer*, Vector2f, const char* texture = "Small_Dot_32.png");
	~Dot(void);
};

#endif // DOT_H