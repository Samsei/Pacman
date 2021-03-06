#ifndef MOVABLEGAMEENTITY_H
#define MOVABLEGAMEENTITY_H

#include "GameEntity.h"

class MovableGameEntity : public GameEntity
{
public:
	MovableGameEntity(SDL_Renderer*, const Vector2f&, const char*, const Vector2f);
	~MovableGameEntity(void);

	void reset();

	bool isAtDestination();

	Vector2f getCurrentTile() const { return current_tile; }

	int speed = 0;

protected:
	void changeDirection();
	void moveEntity(float);
	void setNextTile(Vector2f);
	void moveSprite();


	float distance_to_move = 0.0f;

	Vector2f current_tile = { 0.0f, 0.0f };
	Vector2f entity_next_tile = { 0.0f, 0.0f };
	Vector2f destination = { 0.0f, 0.0f };
	Vector2f direction = { 0.0f, 0.0f };
	Vector2f spawn = { 0.0f, 0.0f };
};

#endif // MOVABLEGAMEENTITY_H