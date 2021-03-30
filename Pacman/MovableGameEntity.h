#ifndef MOVABLEGAMEENTITY_H
#define MOVABLEGAMEENTITY_H

#include "GameEntity.h"
#include "Vector2f.h"

class MovableGameEntity : public GameEntity
{
public:
	MovableGameEntity(const Vector2f&, Sprite*);
	~MovableGameEntity(void);

	bool isAtDestination();

	Vector2f getCurrentTile() const { return current_tile; }

	void setNextTile(float, float);

protected:
	Vector2f current_tile = { 0, 0 };
	Vector2f entity_next_tile = { 0, 0 };
};

#endif // MOVABLEGAMEENTITY_H