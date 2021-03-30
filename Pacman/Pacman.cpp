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
{
	world = new World(main_renderer->returnRenderer());

	player = new Avatar(main_renderer->returnRenderer(), Vector2f(player_spawn.x * tile_size, player_spawn.y * tile_size));

	ghost = new Ghost(Vector2f(player_spawn.x * tile_size, player_spawn.y * tile_size), main_renderer->returnRenderer(), "ghost_32_pink.png", player, world);
}

Pacman::~Pacman(void)
{
	if (player)
	{
		delete player;
		player = NULL;
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

	if (ghost)
	{
		delete ghost;
		ghost = NULL;
	}
}

bool Pacman::init()
{
	world->init();

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
	
	if (immortal_timer > 0)
	{
		immortal_timer -= delta_time;
	}

	hitGhost();
	player->updateInput(next_movement, world);
	player->update(delta_time);

	ghost->update(delta_time, player);

	updateScore();
	checkGhostTimer(delta_time);

	return true;
}

void Pacman::checkGhostTimer(float delta_time)
{
	ghost_timer -= delta_time;

	if (ghost_timer <= 0)
	{
		ghost->is_vulnerable = false;
		ghost->speed = 25.0f;
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
		ghost_timer = 20.0f;
		ghost->is_vulnerable = true;
		ghost->speed = 15.0f;
	}
	
	else if (world->hasIntersectedCherry(player->getPosition()))
	{
		score += 100;
	}
}

void Pacman::hitGhost()
{
	if ((ghost->getPosition() - player->getPosition()).Length() <= 10.0f)
	{
		if (ghost_timer <= 0.0f && immortal_timer <= 0.0f)
		{
			lives--;

			player->reset();
			ghost->reset(player);

			immortal_timer = 3.0f;
		}
		else if (ghost->is_vulnerable && !ghost->is_dead)
		{
			score += 50;
			ghost->is_dead = true;
			ghost->die();
		}
	}
}

bool Pacman::updateInput()
{
	if (keystate[SDL_SCANCODE_UP])
	{ 
		next_movement = Vector2f(0.0f, -1.0f);
	}
	else if (keystate[SDL_SCANCODE_DOWN])
	{
		next_movement = Vector2f(0.0f, 1.0f);
	}
	else if (keystate[SDL_SCANCODE_RIGHT])
	{
		next_movement = Vector2f(1.0f, 0.0f);
	}
	else if (keystate[SDL_SCANCODE_LEFT])
	{
		next_movement = Vector2f(-1.0f, 0.0f);//made if statements more readable
	}
	else if (keystate[SDL_SCANCODE_ESCAPE])
	{
		return false;
	}

	return true;
}

bool Pacman::checkEndGameCondition()
{
	if (world->checkDotList())
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
	renderer->drawText("Score: ", 20, 50);
	renderer->drawText(std::to_string(score).c_str(), 110, 50);

	renderer->drawText("Lives: ", 20, 80);
	renderer->drawText(std::to_string(lives).c_str(), 110, 80);

	renderer->drawText("FPS: ", 880, 50);
	renderer->drawText(std::to_string(fps).c_str(), 940, 50);
}