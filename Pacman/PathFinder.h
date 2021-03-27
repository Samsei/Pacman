#pragma once

#include "Avatar.h"
#include "World.h"

class PathFinder
{
public:
	PathFinder(Avatar*, int, World*);

private:
	int ghost_intelligence = 0;

	Avatar* player = nullptr;
	World* world = nullptr;
};