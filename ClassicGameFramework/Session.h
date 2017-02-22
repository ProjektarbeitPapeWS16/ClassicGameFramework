#pragma once
#include "Config.h"


class Level;


class Session
{
protected:
	int lifes;
	unsigned __int64 creationTime = Config::currentTimeMillis();
	int score;
	Level* level;	//[C] bei Init: Startbildschirm?

public:
	// Konstruktor
	Session();
	Session(int defaultLifes, int defaultScore);

	int getLifes();
	void setLifes(int lifes);

	unsigned __int64 getCreationTime();
	unsigned __int64 getPassedTime();

	int getScore();
	void setScore(int score);

	Level* getLevel();
	void setLevel(Level* level);
};
