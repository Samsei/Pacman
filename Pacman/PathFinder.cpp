#include "PathFinder.h"

PathFinder::PathFinder(Avatar* avatar, int intelligence, World* main_world) :
	player(avatar),
	ghost_intelligence(intelligence),
	world(main_world)
{

}