#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "Vector2f.h"
#include "Drawer.h"

class Drawer;

class GameEntity
{
public:
	GameEntity(SDL_Renderer*, const Vector2f&, const char*);
	~GameEntity(void);

	void draw(Drawer*);

	void setPosition(const Vector2f& new_position) { position = new_position; };

	bool intersect(Vector2f);

	Vector2f getPosition() const { return position; }

protected:
	const int height_offset = 60;
	const int tile_size = 22;
	const int width_offset = 220;

	Vector2f position = { 0.0f, 0.0f };

	Sprite* sprite = nullptr;
};

#endif // GAMEENTITY_H