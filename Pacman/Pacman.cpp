#include "Pacman.h"

//create pacman with a pointer to the drawer
Pacman* Pacman::Create(Drawer* drawer)
{
	Pacman* pacman = new Pacman(drawer);
	return pacman;
}

//create the world, player and ghost, and assign the pointer to "renderer"
Pacman::Pacman(Drawer* main_renderer)
: renderer(main_renderer)
{
	world = new World(main_renderer->returnRenderer());

	//if world fails to create
	if (!world->init())
	{
		return;
	}

	player = new Avatar(main_renderer->returnRenderer(), player_spawn * tile_size, player_spawn);
	ghost = new Ghost(main_renderer->returnRenderer(), Vector2f(ghost_spawn.x * tile_size, ghost_spawn.y * tile_size), "ghost_32_pink.png", player, world, ghost_spawn);
}

//destruct objects and set pointers to null
Pacman::~Pacman(void)
{
	if (player)
	{
		delete player;
		player = NULL;
	}
	if (world)
	{
		delete world;
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
	if (renderer)
	{
		renderer = NULL;
	}
}

//core game loop, update each object and check win/loss conditions
bool Pacman::update(float delta_time)
{
	//if escape is pressed, exit
	if (!updateInput())
	{
		return false;
	}

	//if game has ended, exit
	if (!checkEndGameCondition())
	{
		return false;
	}

	hitGhost();
	updateScore();
	checkTimers(delta_time);

	player->updateInput(next_movement, world);
	player->update(delta_time);
	ghost->update(delta_time);

	return true;
}

//update various timers used for the game
void Pacman::checkTimers(float delta_time)
{
	if (delta_time > 0)
	{
		fps = (1 / delta_time);
	}

	if (ghost_timer > 0)
	{
		ghost_timer -= delta_time;
	}

	if (ghost_timer <= 0)
	{
		ghost->setNormal();
	}

	if (immortal_timer > 0)
	{
		immortal_timer -= delta_time;
	}
}

//check if the player is at the destination tile and if that tile contains an entity
void Pacman::updateScore()
{
	if (player->isAtDestination() && world->hasIntersectedDot(player->getPosition()))
	{
		score += 10;
	}

	else if (player->isAtDestination() && world->hasIntersectedBigDot(player->getPosition()))
	{
		score += 20;
		ghost_timer = 20.0f;
		ghost->setVulnerable();
	}
	
	else if (player->isAtDestination() && world->hasIntersectedCherry(player->getPosition()))
	{
		score += 100;
	}
}

//check if the ghost has hit the player, and check if it is vulnerable
void Pacman::hitGhost()
{
	if ((ghost->getPosition() - player->getPosition()).Length() <= 10.0f)
	{
		if (ghost_timer <= 0.0f && immortal_timer <= 0.0f)
		{
			player->reset();
			ghost->reset();
			lives--;
			immortal_timer = 3.0f;
		}
		else if (ghost->is_vulnerable && !ghost->is_dead)
		{
			score += 50;
			ghost->setDead();
		}
	}
}

//check if the player has collected all dots, or if the life total is 0 or less
bool Pacman::checkEndGameCondition()
{
	if (score >= 2000 && world->checkDotList())
	{
		renderer->drawText("You win!", 20, 70);
		SDL_Delay(5000);
		return false;
	}

	if (lives <= 0)
	{
		renderer->drawText("You lose!", 20, 70);
		SDL_Delay(5000);
		return false;
	}

	return true;
}

//update the input
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

//draw the objects
bool Pacman::draw()
{
	world->draw(renderer);
	player->draw(renderer);
	ghost->draw(renderer);

	drawText();	

	return true;
}

//draw text relating to score, lives and fps
void Pacman::drawText()
{
	renderer->drawText("Score: ", 20, 50);
	renderer->drawText(std::to_string(score).c_str(), 110, 50);

	renderer->drawText("Lives: ", 20, 80);
	renderer->drawText(std::to_string(lives).c_str(), 110, 80);

	renderer->drawText("FPS: ", 880, 50);
	renderer->drawText(std::to_string(fps).c_str(), 940, 50);
}