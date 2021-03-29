#include "PathmapTile.h"

PathmapTile::PathmapTile(int x, int y, bool is_blocking, bool is_spawn): 
	x(x), 
	y(y), 
	is_blocking(is_blocking),
	is_spawn(is_spawn)
{
}