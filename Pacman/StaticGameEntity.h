#ifndef STATICGAMEENTITY_H
#define STATICGAMEENTITY_H

#include "GameEntity.h"
#include "Vector2f.h"

class StaticGameEntity : public GameEntity
{
public:
	StaticGameEntity(SDL_Renderer*, Vector2f, const char*);
	~StaticGameEntity(void);
};

#endif // STATICGAMEENTITY_H