#include "PathmapTile.h"

//create tile at x and y and check if it is a wall
PathmapTile::PathmapTile(int x, int y, bool is_blocking):
	x(x), 
	y(y), 
	is_blocking(is_blocking)
{
}

//destruct and set pointer to null
PathmapTile::~PathmapTile()
{
	if (parent)
	{
		parent = NULL;
	}
}

//return the current tile as a vector 
Vector2f PathmapTile::returnTileAsVector()
{
	return Vector2f{ x, y };
}