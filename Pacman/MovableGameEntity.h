#ifndef MOVABLEGAMEENTITY_H
#define MOVABLEGAMEENTITY_H

#include "GameEntity.h"

class MovableGameEntity : public GameEntity
{
public:
	MovableGameEntity(SDL_Renderer*, const Vector2f&, const char*);
	~MovableGameEntity(void);

	Vector2f getCurrentTile() const { return current_tile; }

protected:
	void changeDirection();
	void moveEntity(float);
	void setNextTile(float, float);
	void moveSprite();

	bool isAtDestination();


	float distance_to_move = 0.0f;

	int speed = 30;

	Vector2f current_tile = { 0.0f, 0.0f };
	Vector2f entity_next_tile = { 0.0f, 0.0f };
	Vector2f destination = { 0.0f, 0.0f };
	Vector2f direction = { 0.0f, 0.0f };
};

#endif // MOVABLEGAMEENTITY_H