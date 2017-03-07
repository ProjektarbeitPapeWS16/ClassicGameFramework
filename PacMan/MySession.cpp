#include "MySession.h"



MySession::MySession() : Session()
{
	setLevel(new MyLevel(100, 100, 1, 1));
}


MySession::~MySession()
{
}

void MySession::nextIteration()
{
	switch (static_cast<MyLevel*>(getLevel())->gameState)
	{
	case MyLevel::RESTARTGAME:
		setLevel(new MyLevel(100, 100, 1, 1));
	default:
		static_cast<MyLevel*>(getLevel())->gameLoop();
	}

	//gameState = getMyLevel()->getGameStateRequest(); TODO
	/*
	switch (gameState)
	{
	case MyLevel::NORMAL:
		static_cast<MyLevel*>(getLevel())->gameLoop();
		break;
	case MyLevel::PACMANDEAD:
		setLevel(new MyLevel(100, 100, 1, 1));
		break;
	case MyLevel::PAUSE:
		break;
	case MyLevel::RESTARTGAME:
		setLevel(new MyLevel(100, 100, 1, 1));
		break;
	}
	*/
}

MyLevel* MySession::getMyLevel()
{
	return static_cast<MyLevel*>(level);
}