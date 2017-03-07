#pragma once
#include "Session.h"
#include "MyLevel.h"

class MySession : public Session
{
public:
	MySession();
	~MySession();

	void nextIteration();

private:
	MyLevel::GameState gameState = MyLevel::NORMAL;

	MyLevel* getMyLevel();
};

