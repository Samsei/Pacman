#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "Vector2f.h"
#include "Drawer.h"

class Drawer;

class GameEntity
{
public:
	GameEntity(const Vector2f&, Sprite*);
	~GameEntity(void);

	virtual void draw(Drawer*);
	void setPosition(const Vector2f& aPosition) { position = aPosition; }

	bool intersect(GameEntity*);

	Vector2f getPosition() const { return position; }

protected:

	bool marked_for_delete = false;

	Vector2f position = { 0.0f, 0.0f };

	Sprite* sprite = nullptr;
};

#endif // GAMEENTITY_H