#include "PathmapTile.h"

PathmapTile::PathmapTile(int x, int y, bool is_blocking)
: x(x)
, y(y)
, is_blocking(is_blocking)
,is_visited(false)
{
}