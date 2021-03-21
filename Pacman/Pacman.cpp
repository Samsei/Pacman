#include "Pacman.h"

Pacman* Pacman::Create(Drawer* aDrawer)
{
	Pacman* pacman = new Pacman(aDrawer);

	if (!pacman->Init())
	{
		delete pacman;
		pacman = NULL;
	}

	return pacman;
}

Pacman::Pacman(Drawer* aDrawer)
: myDrawer(aDrawer)
, myTimeToNextUpdate(0.f)
, myNextMovement(-1.f,0.f)
, myScore(0)
, myFps(0)
, myLives(3)
, myGhostGhostCounter(0.f)
{
	myAvatar = new Avatar(aDrawer->ReturnRenderer(), Vector2f(13*22,22*22));
	myGhost = new Ghost(Vector2f(13*22,13*22), aDrawer->ReturnRenderer());
	myWorld = new World(aDrawer->ReturnRenderer());
}

Pacman::~Pacman(void)
{
	delete myAvatar;
	myAvatar = NULL;
	delete myGhost;
	myGhost = NULL;
	delete myWorld;//memory
	myWorld = NULL;
	delete avatarSprite;
	avatarSprite = NULL;
}

bool Pacman::Init()
{
	myWorld->Init(myDrawer);

	return true;
}

bool Pacman::Update(float aTime)
{
	if (!UpdateInput())
	{
		return false;
	}

	if (!CheckEndGameCondition())
	{
		return false;
	}

	MoveAvatar();
	myAvatar->Update(aTime);
	myGhost->Update(aTime, myWorld);

	UpdateScore(); //made own function
	CheckGhostTimer(aTime);
	HitGhost();
	
	if (aTime > 0)
	{
		myFps = (int)(1 / aTime);
	}
	return true;
}

void Pacman::CheckGhostTimer(float aTime)
{
	myGhostGhostCounter -= aTime;

	if (myGhostGhostCounter <= 0)
	{
		myGhost->myIsClaimableFlag = false;
	}
}

void Pacman::UpdateScore()
{
	if (myWorld->HasIntersectedDot(myAvatar->GetPosition()))
		myScore += 10;

	if (myWorld->HasIntersectedBigDot(myAvatar->GetPosition()))
	{
		myScore += 20;
		myGhostGhostCounter = 20.f;
		myGhost->myIsClaimableFlag = true;
	}
}

void Pacman::HitGhost()
{
	if ((myGhost->GetPosition() - myAvatar->GetPosition()).Length() < 10.f)
	{
		if (myGhostGhostCounter <= 0.f)
		{
			myLives--;

			myAvatar->SetPosition(Vector2f(13 * 22, 22 * 22));
			myGhost->SetPosition(Vector2f(13 * 22, 13 * 22));
		}
		else if (myGhost->myIsClaimableFlag && !myGhost->myIsDeadFlag)
		{
			myScore += 50;
			myGhost->myIsDeadFlag = true;
			myGhost->Die(myWorld);
		}
	}
}

bool Pacman::UpdateInput()
{
	if (keystate[SDL_SCANCODE_UP])
	{ 
		myNextMovement = Vector2f(0.f, -1.f);
	}
	else if (keystate[SDL_SCANCODE_DOWN])
	{
		myNextMovement = Vector2f(0.f, 1.f);
	}
	else if (keystate[SDL_SCANCODE_RIGHT])
	{
		myNextMovement = Vector2f(1.f, 0.f);
	}
	else if (keystate[SDL_SCANCODE_LEFT])
	{
		myNextMovement = Vector2f(-1.f, 0.f);//made if statements more readable
	}
	/*else
	{
		myNextMovement = Vector2f(0.f, 0.f);//add no movement
	}*/

	if (keystate[SDL_SCANCODE_ESCAPE])
	{
		return false;
	}
	return true;
}

void Pacman::MoveAvatar()
{
	nextTileX = myAvatar->GetCurrentTileX() + myNextMovement.myX;
	nextTileY = myAvatar->GetCurrentTileY() + myNextMovement.myY;

	if (myAvatar->IsAtDestination() && myWorld->TileIsValid(nextTileX, nextTileY))  //unnested if statementa
	{
		myAvatar->SetNextTile(nextTileX, nextTileY);
	}
}

bool Pacman::CheckEndGameCondition()
{
	if (myScore == 10000000)
	{
		myDrawer->DrawText("You win!", 20, 70);
		return false;
	}

	if (myLives <= 0)
	{
		myDrawer->DrawText("You lose!", 20, 70);
		return false;
	}

	return true;
}

bool Pacman::Draw()
{
	myWorld->Draw(myDrawer);
	myAvatar->Draw(myDrawer);
	myGhost->Draw(myDrawer);

	DrawText();	

	return true;
}

void Pacman::DrawText()
{
	std::string scoreString;
	std::stringstream scoreStream;
	std::string livesString;
	std::stringstream liveStream;
	std::string fpsString;
	std::stringstream fpsStream;

	scoreStream << myScore;
	scoreString = scoreStream.str();
	myDrawer->DrawText("Score", 20, 50);
	myDrawer->DrawText(scoreString.c_str(), 90, 50);

	liveStream << myLives;
	livesString = liveStream.str();
	myDrawer->DrawText("Lives", 20, 80);
	myDrawer->DrawText(livesString.c_str(), 90, 80);

	myDrawer->DrawText("FPS", 880, 50);

	fpsStream << myFps;
	fpsString = fpsStream.str();
	myDrawer->DrawText(fpsString.c_str(), 930, 50);
}