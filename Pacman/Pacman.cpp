#include "Pacman.h"

Pacman* Pacman::Create(Drawer* aDrawer)
{
	Pacman* pacman = new Pacman(aDrawer);

	if (!pacman->init())
	{
		delete pacman;
		pacman = NULL;
	}

	return pacman;
}

Pacman::Pacman(Drawer* main_renderer)
: renderer(main_renderer)
, time_to_next_update(0.f)
, next_movement(-1.f,0.f)
, score(0)
, fps(0)
, lives(3)
, ghost_timer(0.f)
{
	player = new Avatar(main_renderer->returnRenderer(), Vector2f(13*22,22*22));
	ghost = new Ghost(Vector2f(13*22,13*22), main_renderer->returnRenderer());
	world = new World(main_renderer->returnRenderer());
}

Pacman::~Pacman(void)
{
	if (player)
	{
		delete player;
		player = NULL;
	}

	if (ghost)
	{
		delete ghost;
		ghost = NULL;
	}

	if (world)
	{
		delete world;//memory
		world = NULL;
	}

	if (player_sprite)
	{
		delete player_sprite;
		player_sprite = NULL;
	}	
}

bool Pacman::init()
{
	world->init(renderer);

	return true;
}

bool Pacman::update(float delta_time)
{
	if (!updateInput())
	{
		return false;
	}

	if (!checkEndGameCondition())
	{
		return false;
	}

	if (delta_time > 0)
	{
		fps = (int)(1 / delta_time);
	}

	movePlayer();
	player->update(delta_time);
	ghost->update(delta_time, world);

	updateScore();
	checkGhostTimer(delta_time);
	hitGhost();

	return true;
}

void Pacman::checkGhostTimer(float delta_time)
{
	ghost_timer -= delta_time;

	if (ghost_timer <= 0)
	{
		ghost->is_vulnerable = false;
	}
}

void Pacman::updateScore()
{
	if (world->hasIntersectedDot(player->getPosition()))
	{
		score += 10;
	}

	else if (world->hasIntersectedBigDot(player->getPosition()))
	{
		score += 20;
		ghost_timer = 20.f;
		ghost->is_vulnerable = true;
	}
	
	else if (world->hasIntersectedCherry(player->getPosition()))
	{
		score += 100;
	}
}

void Pacman::hitGhost()
{
	if ((ghost->getPosition() - player->getPosition()).Length() < 10.f)
	{
		if (ghost_timer <= 0.f)
		{
			lives--;

			player->setPosition(Vector2f(13 * 22, 22 * 22));
			ghost->setPosition(Vector2f(13 * 22, 13 * 22));
		}
		else if (ghost->is_vulnerable && !ghost->is_dead)
		{
			score += 50;
			ghost->is_dead = true;
			ghost->die(world);
		}
	}
}

bool Pacman::updateInput()
{
	if (keystate[SDL_SCANCODE_UP])
	{ 
		next_movement = Vector2f(0.f, -1.f);
	}
	else if (keystate[SDL_SCANCODE_DOWN])
	{
		next_movement = Vector2f(0.f, 1.f);
	}
	else if (keystate[SDL_SCANCODE_RIGHT])
	{
		next_movement = Vector2f(1.f, 0.f);
	}
	else if (keystate[SDL_SCANCODE_LEFT])
	{
		next_movement = Vector2f(-1.f, 0.f);//made if statements more readable
	}

	if (keystate[SDL_SCANCODE_ESCAPE])
	{
		return false;
	}
	return true;
}

void Pacman::movePlayer()
{
	entity_next_tile_x = player->getCurrentTileX() + next_movement.x;
	entity_next_tile_y = player->getCurrentTileY() + next_movement.y;

	if (player->isAtDestination() && world->tileIsValid(entity_next_tile_x, entity_next_tile_y))  //unnested if statement
	{
		player->setNextTile(entity_next_tile_x, entity_next_tile_y);
	}
}

bool Pacman::checkEndGameCondition()
{
	if (score == 10000000)
	{
		renderer->drawText("You win!", 20, 70);
		return false;
	}

	if (lives <= 0)
	{
		renderer->drawText("You lose!", 20, 70);
		return false;
	}

	return true;
}

bool Pacman::draw()
{
	world->draw(renderer);
	player->draw(renderer);
	ghost->draw(renderer);

	drawText();	

	return true;
}

void Pacman::drawText()
{
	renderer->drawText("Score", 20, 50);
	renderer->drawText(std::to_string(score).c_str(), 90, 50);

	renderer->drawText("Lives", 20, 80);
	renderer->drawText(std::to_string(lives).c_str(), 90, 80);

	renderer->drawText("FPS", 880, 50);
	renderer->drawText(std::to_string(fps).c_str(), 930, 50);
}