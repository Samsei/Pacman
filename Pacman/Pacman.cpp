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
	avatarSprite = new Sprite(aDrawer->ReturnRenderer(), "open_32.png");

	myAvatar = new Avatar(aDrawer->ReturnRenderer(), Vector2f(13*22,22*22), avatarSprite);
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
		return false;

	if (CheckEndGameCondition())
	{
		myDrawer->DrawText("You win!", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 70);
		return true;
	}
	else if (myLives <= 0)
	{
		myDrawer->DrawText("You lose!", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 70);	
		return true;
	}

	MoveAvatar();
	myAvatar->Update(aTime);
	myGhost->Update(aTime, myWorld);

	UpdateScore(); //made own function

	myGhostGhostCounter -= aTime;	

	if (myGhostGhostCounter <= 0)
	{
		myGhost->myIsClaimableFlag = false;
	}

	if ((myGhost->GetPosition() - myAvatar->GetPosition()).Length() < 10.f)
	{
		if (myGhostGhostCounter <= 0.f)
		{
			myLives--;

			myAvatar->SetPosition(Vector2f(13*22,22*22));
			myGhost->SetPosition(Vector2f(13*22,13*22));
		}
		else if (myGhost->myIsClaimableFlag && !myGhost->myIsDeadFlag)
		{
			myScore += 50;
			myGhost->myIsDeadFlag = true;
			myGhost->Die(myWorld);
		}
	}
	
	if (aTime > 0)
		myFps = (int) (1 / aTime);

	return true;
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
	else
	{
		myNextMovement = Vector2f(0.f, 0.f);//add no movement
	}

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
	return false;
}

bool Pacman::Draw()
{
	std::string scoreString;
	std::stringstream scoreStream;
	std::string livesString;
	std::stringstream liveStream;
	std::string fpsString;
	std::stringstream fpsStream;

	myWorld->Draw(myDrawer);
	myAvatar->Draw(myDrawer);
	myGhost->Draw(myDrawer);


	scoreStream << myScore;
	scoreString = scoreStream.str();
	myDrawer->DrawText("Score", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 50);
	myDrawer->DrawText(scoreString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 90, 50);

	
	liveStream << myLives;
	livesString = liveStream.str();
	myDrawer->DrawText("Lives", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 80);
	myDrawer->DrawText(livesString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 90, 80);

	myDrawer->DrawText("FPS", "freefont-ttf\\sfd\\FreeMono.ttf", 880, 50);

	fpsStream << myFps;
	fpsString = fpsStream.str();
	myDrawer->DrawText(fpsString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 930, 50);

	return true;
}