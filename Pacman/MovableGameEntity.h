#ifndef MOVABLEGAMEENTITY_H
#define MOVABLEGAMEENTITY_H

#include "GameEntity.h"
#include "Vector2f.h"

class MovableGameEntity : public GameEntity
{
public:
	MovableGameEntity(const Vector2f&, Sprite*);
	~MovableGameEntity(void);

	void setNextTile(int, int);

	int getCurrentTileX() const { return current_tile_x; }
	int getCurrentTileY() const { return current_tile_y; }

	bool isAtDestination();

protected:
	int current_tile_x = 0;
	int current_tile_y = 0;

	int next_tile_x = 0;
	int next_tile_y = 0;
};

#endif // MOVABLEGAMEENTITY_H